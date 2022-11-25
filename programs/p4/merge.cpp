#include "merge.h"
#include <cctype>
#include <cstddef>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class merge_t {
private:
	string merge;
	vector<bool> second;

public:
	/* represents a view of the merge, specialized for the crazy stuff I do in
	   this program */
	template<typename str_it, typename bool_it, bool forward_it>
	class view_t {
	public:
		/* represents an element of the string */
		struct element_t {
			const char c;
			const bool move_forward;
			const bool move_backward;

			element_t(char c, bool forward)
				: c(c), move_forward(forward), move_backward(!forward) { }
			operator char() { return c; }
		};

		view_t(merge_t& m, str_it si, bool_it bi)
		: m(m), si(si), bi(bi) { }

		element_t operator[](size_t i) {
			// if forward-iterating, first-string characters move forward
			if (forward_it) return element_t(si[i], !bi[i]);
			else return element_t(si[i], bi[i]);
		}

		size_t size() { return m.size(); }

		bool swap(size_t i, size_t j) {
			if (si[i] != si[j]) return false;

			// can't use ::swap() here, as it doesn't like bitrefs
			bool t = bi[i];
			bi[i] = bi[j];
			bi[j] = t;

			return true;
		}

	private:
		merge_t& m;
		str_it si;
		bool_it bi;
	};

	using forward_view = view_t<decltype(merge.begin()),
	                            decltype(second.begin()),
	                            true>;
	using reverse_view = view_t<decltype(merge.rbegin()),
	                            decltype(second.rbegin()),
	                            false>;

	merge_t(const string& m) : merge(m), second(m.size()) { }

	/* mark the latest possible positions that second-string characters could
	   occur */
	bool mark_seconds(const string& sec) {
		ssize_t sec_i = sec.size() - 1;
		for (ssize_t i = merge.size() - 1; i > -1 && sec_i > -1; --i) {
			if (merge[i] == sec[sec_i]) { // found a match, put it here
				second[i] = true;
				--sec_i;
			}
		}

		return sec_i == -1; // placed all the characters!
	}

	/* check if the characters not marked as seconds permit a merge */
	bool check_firsts(const string& fir) {
		ssize_t counts[26];
		ssize_t i;

		for (i = 0; i < 26; ++i) counts[i] = 0;
		for (i = 0; i < merge.size(); ++i) {
			if (!second[i]) ++counts[merge[i] - 'a'];
		}
		for (i = 0; i < fir.size(); ++i) {
			--counts[fir[i] - 'a'];
		}
		for (i = 0; i < 26; ++i) {
			if (counts[i] != 0) return false;
		}
		return true; // either they match or some SERIOUS rollover occurred
	}

	/* check if whatever we have is a valid solution */
	bool verify(const string& fir, const string& sec) {
		ssize_t m_i = 0;
		ssize_t fir_i = 0;
		ssize_t sec_i = 0;

		for (; m_i < merge.size(); ++m_i) {
			if (!second[m_i]) { // came from first
				// if we ran out of characters or don't match, return!
				if (fir_i == fir.size() || fir[fir_i] != merge[m_i]) {
					return false;
				}
				++fir_i;
			} else {
				if (sec_i == sec.size() || sec[sec_i] != merge[m_i]) {
					return false;
				}
				++sec_i;
			}
		}

		// finally, see if we made it to the end
		return m_i == merge.size()
			&& fir_i == fir.size()
			&& sec_i == sec.size();
	}

	forward_view forward() {
		return forward_view(*this, merge.begin(), second.begin());
	}

	reverse_view reverse() {
		return reverse_view(*this, merge.rbegin(), second.rbegin());
	}

	size_t size() {
		return merge.size();
	}

	string str() const {
		string ret(merge);
		for (size_t i = 0; i < merge.size(); ++i) {
			// capitalize when necessary
			if (!second[i]) ret[i] = toupper(ret[i]);
		}
		return ret;
	}
};

ostream& operator<<(ostream& out, const merge_t& m) {
	return out << m.str();
}

/* percolate incorrect characters in the wrong directions */
template<typename view_t, typename str_t>
bool percolate(view_t& m, const str_t s) {
	const size_t size = m.size();

	ssize_t si = 0;
	for (ssize_t i = 0; i < size; ++i) {
		if (m[i].move_forward) {
			// first string, so see if it's in the right place
			bool right = s[si] == m[i].c;
			if (!right) {
				// this character came too soon, so push it into the next
				// block of seconds
				const char looking_for = m[i].c;

				// scroll forward to a character that might work
				ssize_t j = i + 1;
				for (; j < size; ++j) {
					if (m[j].move_backward && m[j].c == looking_for) break;
				}

				if (j < size) {
					// found one, so do a swap
					m.swap(i, j);
					return true;
				}
			}

			++si;
		}
	}

	return false;
}

/* improve the strings until they stabilize */
void improve(merge_t& m, const string& fir, const string& sec) {
	auto m_for = m.forward();
	auto fir_for = fir.begin();

	auto m_rev = m.reverse();
	auto sec_rev = sec.rbegin();

	// note: do *not* use a shortcut OR here!
	while (percolate(m_for, fir_for) | percolate(m_rev, sec_rev));
}

pair<bool, string> is_merge_of(const string& merge,
                               const string& first,
                               const string& second) {
	// run some preliminary checks
	merge_t m(merge);
	if (!m.mark_seconds(second) || !m.check_firsts(first)) {
		goto not_a_merge;
	}

	// do what we can with the merge
	improve(m, first, second);

	// return what we got
	if (!m.verify(first, second)) goto not_a_merge;
	return pair<bool, string>(true, m.str());

not_a_merge:
	return pair<bool, string>(false, "");
}

/*
Copyright (C) 2022  Catherine Van West

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

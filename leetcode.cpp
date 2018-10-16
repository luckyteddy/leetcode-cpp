#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <algorithm>
#include <stack>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> record {};
		for (int i = 0; i != nums.size(); ++i) {
			cout << i << " ";
			auto found = record.find(nums[i]);
			if (found != record.end()) {
				cout << nums[found->second] << " " << nums[i];
				return { found->second, i };
			}
			record.emplace(target - nums[i], i);
		}
		return { -1, -1 };
	}

	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = new ListNode(0);
		ListNode* cur = head;
		int sum;
		int carry = 0;
		while (l1 != NULL || l2 != NULL) {
			sum = 0;
			if (l1) { sum += l1->val; l1 = l1->next; }
			if (l2) { sum += l2->val; l2 = l2->next; }
			sum += carry;
			if (sum < 10) {
				cur->next = new ListNode(sum);
				cur = cur->next;
				carry = 0;
				cout << sum;
			}
			else {
				cur->next = new ListNode(sum % 10);
				cur = cur->next;
				carry = 1;
				cout << sum;
			}
		}
		if (carry) {
			cur->next = new ListNode(1);
			cur = cur->next;
		}
		return head->next;
	}

	int lengthOfLongestSubstring(string s) {
		set<char> set1{};
		int maxlen = 0, curlen = 0;
		int start = 0;
		for (int t = 0; t < s.length(); t++) {
			if (set1.find(s[t]) == set1.end()) {
				set1.emplace(s[t]);
				curlen = t - start + 1;
			}
			else {
				int t1 = start;
				while (s[t1]!=s[t]){	
					set1.erase(s[t1]);
					t1++;
				}
				start = t1 + 1;
			}
			maxlen = max(maxlen, curlen);
		}
		return maxlen;
	}

	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int len1 = nums1.size(); 
		int len2 = nums2.size();
		if (len1 + len2 == 1) {
			nums1.insert(nums1.end(), nums2.begin(), nums2.end());
			return nums1[0];
		}
		if ((len1 + len2) % 2 == 1) {
			return find_Kth(nums1, 0, nums2, 0, (len1 + len2) / 2 + 1);
		}
		else {
			return (find_Kth(nums1, 0, nums2, 0, (len1 + len2) / 2 ) + find_Kth(nums1, 0, nums2, 0, (len1 + len2) / 2 +1))/2;
		}

	}

	string longestPalindrome(string s) {
		string maxPal;
		int maxlen(0);

		for (int i = 0; i < s.length(); i++) {

			int first = i;
			int end = i;
			while (s[i] == s[i + 1]) {
				end++;
				i++;
			}
			while (first > 0 && end < s.length()-1 && s[first-1] == s[end+1]) {
				first--;
				end++;
			}
			if (end - first + 1 > maxlen) {
				maxlen = end - first + 1;
				maxPal = s.substr(first, maxlen);
				
			}
		}
		cout << maxlen << " " << maxPal;
		return maxPal;
	}

	string convert(string s, int numRows) {
		if (numRows == 1) return s;
		string ans("");
		int lens = s.length();
		int inter = numRows - 2;
		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < ceil((float)s.length() / numRows); j++) {
				if (j * (numRows + inter) + i < lens){
					ans.append(1, s[j * (numRows + inter) + i]);
				}
				if ((i != 0 && i != numRows - 1) && (j*(numRows + inter) + i + 2 * (numRows - i - 1)<lens)) {
					ans.append(1, s[j*(numRows + inter) + i + 2 *(numRows-i-1)]);
				}
			}
		}
		cout << ans;
		return ans;
	}

	int reverse(int x) {
		int y = 0;
		int t;
		while (x != 0) {
			t = y * 10 + x % 10;
			if (t / 10 != y) return 0;
			y = t;
			x = x / 10;
		}
		return y;
	}

	int myAtoi(string str) {
		int sign = 1;
		int start = 0;
		int val = 0;
		for (int ptr = 0; ptr < str.length(); ptr++) {
			if (start == 0 && str[ptr] == ' ') continue;
			if (start == 0 && !isdigit(str[ptr])) {
				if (str[ptr] == '-') sign = -1; 
				else if (str[ptr] == '+') sign = 1; 
				else  break; 
				start = 1;
				continue;
			}
			if (start == 0 && isdigit(str[ptr])) {
				start = 1;
				if (ptr-1 >= 0 && str[ptr - 1] == '-') sign = -1;
			}
			if (start == 1 && !isdigit(str[ptr])) break;
			if (start == 1 && isdigit(str[ptr])) {
				int t = val * 10 + (str[ptr] - '0');
				if (t / 10 != val) {
					if (sign == -1) return INT_MIN;
					else return INT_MAX;
				}
				val = t;
			}
		}
		return sign * val;
	}

	bool isPalindrome(int x) {
		int y = 0;
		int t = x;
		if (x == 0) return true;
		if (x < 0) return false;
		while (t != 0) {
			y = y * 10 + t % 10;
			t = t / 10;
		}
		if (x == y) return true;
		else return false;
	}

	int maxArea(vector<int>& height) {
		auto begin=height.begin();
		auto end=height.end();
		end--;
		int ma = 0;
		int area = 0;
		while (begin != end) {
			if (*begin > *end) {
				area = *end * (end - begin);
				ma = max(ma, area);
				end--;
			}
			else {
				area = *begin * (end - begin);
				ma = max(ma, area);
				begin++;
			}
		}
		return ma;
	}

	string intToRoman(int num) {
		string s{""};
		while (num / 1000 != 0) {
			s += "M";
			num -= 1000;
		}
		while (num / 100 != 0) {
			if (num / 100 == 9) {
				s += "CM"; num -= 900;
			}
			else if (num / 100 >= 5) {
				s += "D"; num -= 500;
			}
			else if (num / 100 >= 4) {
				s += "CD"; num -= 400;
			}
			else {
				s += "C"; num -= 100;
			}
		}
		while (num / 10 != 0) {
			if (num / 10 == 9) {
				s += "XC"; num -= 90;
			}
			else if (num / 10 == 4) {
				s += "XL"; num -= 40;
			}
			else if (num / 10 >= 5) {
				s += "L"; num -= 50;
			}
			else {
				s += "X"; num -= 10;
			}
		}
		while (num / 1 != 0) {
			if (num / 1 == 9) {
				s += "IX"; num -= 9;
			}
			else if (num / 1 == 4) {
				s += "IV"; num -= 4;
			}
			else if (num / 1 >= 5) {
				s += "V"; num -= 5;
			}
			else {
				s += "I"; num -= 1;
			}
		}
		return s;
	}

	int romanToInt(string s) {
		int t{0};
		unordered_map<char, int> romap;
		romap['I'] = 1;
		romap['V'] = 5;
		romap['X'] = 10;
		romap['L'] = 50;
		romap['C'] = 100;
		romap['D'] = 500;
		romap['M'] = 1000;
		for (int i = s.length()-1; i >= 0; i--) {
			if (i - 1 >= 0 && romap[s[i - 1]] < romap[s[i]]) { t = t + romap[s[i]] - romap[s[i - 1]]; i--; }
			else t = t + romap[s[i]];
		}
		return t;
	}

	string longestCommonPrefix(vector<string>& strs) {
		if (strs.empty()) return "";
		int slen = strs.size();
		string s{};
		char t;
		for (int i = 0; i < strs[0].size(); i++) {
			int flag = 1;
			t = strs[0][i];
			for (int j = 1; j < slen; j++) {
				int curstrlen = strs[j].size();
				if (i > curstrlen - 1) return s;
				if (t != strs[j][i]) return s;
			}
			if (flag == 1) s += t;
		}
		return s;
	}

	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> vvi{};
		vector<int> ans;
		int len = nums.size();
		if (len < 2) return vvi;
		std::sort(nums.begin(), nums.end());
		for (int i = 0; i < len - 2; i++) {
			if (i > 0 && nums[i] == nums[i - 1] || nums[i] > 0) continue;
			int j = i + 1; 
			int k = len - 1;
			int tar = -nums[i];
			while (j < k) {
				if (nums[j] + nums[k] == tar) {
					vvi.push_back({ nums[i], nums[j], nums[k] });
					cout << nums[i] << " " << i << "+" << nums[j] << " " << j << "+" << nums[k] << " " << k << endl;
					j++;
					while (j < len && nums[j] == nums[j - 1]) j++;
					k--;
					while (k > i && nums[k] == nums[k + 1] ) k--;
				}
				else if (nums[j] + nums[k] < tar) {
					j++;
					while (j < len && nums[j] == nums[j - 1]) j++;
				}
				else {
					k--;
					while (k > i && nums[k] == nums[k + 1]) k--;
				}
			}
		}
		return vvi;
	}

	int threeSumClosest(vector<int>& nums, int target) {
		int ans;
		int diff = INT_MAX;
		int len = nums.size();
		if (len < 2) return 0;
		std::sort(nums.begin(), nums.end());
		for (int i = 0; i < len - 2; i++) {
			int j = i + 1;
			int k = len - 1;
			while (j < k) {
				if (abs(nums[i] + nums[j] + nums[k] - target) < diff) {
					ans = nums[i] + nums[j] + nums[k];
					diff = abs(ans - target);
					if (diff == 0) return ans;
				}
				if (nums[i] + nums[j] + nums[k] < target) {
					j++;
					while (j < len && nums[j] == nums[j - 1]) j++;
				}
				else {
					k--;
					while (k > i && nums[k] == nums[k + 1]) k--;
				}
			}
		}
		return ans;
	}

	vector<string> letterCombinations(string digits) {
		unordered_map<char, string> um = { {'0'," "}, {'1', ""}, {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"} ,{'8', "tuv"}, {'9', "wxyz"} };
		vector<string> vs{};
		int leng = digits.size();
		if (leng == 0) return vs;
		letterCombinationDFS(vs, digits, 0, um, "");
		return vs;
	}
	void letterCombinationDFS(vector<string> &vs, string digits, int level, unordered_map<char, string> &um, string out) {
		if (level == digits.size()) {
			vs.push_back(out);
			cout << out << endl;
		}
		else {
			string cur;
			cur = um[digits[level]];
			for (int i = 0; i < cur.size(); i++) {
                out.push_back(cur[i]);
				letterCombinationDFS(vs, digits, level+1, um, out);
				out.pop_back();
			}
		}
	}
	
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		set<vector<int>> vvi;
		sort(nums.begin(),nums.end());
		for (int i1 = 0; i1 < int(nums.size() - 3); i1++) {
			for (int i4 = int(nums.size() - 1); i4 > 2; i4--) {
				int i2 = i1 + 1;
				int i3 = i4 - 1;
				while(i2 < i3) {
					if (nums[i1] + nums[i2] + nums[i3] + nums[i4] == target) {
						vector<int> vi{ nums[i1], nums[i2] , nums[i3] , nums[i4] };
						vvi.insert(vi);
						cout << nums[i1] << "+" << nums[i2] << "+" << nums[i3] << "+" << nums[i4] << endl;
						i2++;
						i3--;
					}
					else if (nums[i1] + nums[i2] + nums[i3] + nums[i4] < target) {
						i2++;
					}
					else i3--;
				}
			}
		}
		vector<vector<int>> vvvi(vvi.begin(), vvi.end());
		return vvvi;
	}

	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* before1 = head;
		ListNode* cur = head;
		for (int i = 0; i < n ; i++) {
			cur = cur->next;
		}
		if (cur == NULL) {
			head = head->next;
		    return head;
		}
		while (cur->next != NULL) {
			cur = cur->next;
			before1 = before1->next;
		}
		cur = before1->next;
		before1->next = cur->next;
		delete(cur);
		return head;
	}

	bool isValid(string s) {
		stack<char> sc;
		char c;
		bool ans;
		for (int i = 0; i < s.size(); i++) {
			c = s[i];
			if (c == '(' || c == '{' || c == '[') sc.push(c);
			if (c == ')' || c == ']' || c == '}') {
				if (c == ')' && ( sc.empty() || sc.top() != '(')) { return false; }
				if (c == '}' && (sc.empty()|| sc.top() != '{')) { return false; }
				if (c == ']' && ( sc.empty()|| sc.top() != '[')) { return false; }
				sc.pop();
			}
		}
		if (!sc.empty()) { return false; }
		else return true;
	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* head, *cur;
		if (l1 == NULL) return l2;
		if (l2 == NULL) return l1;
		head = new ListNode(-1);
		cur = head;
		while (l1 != NULL && l2 != NULL) {
			if (l1->val <= l2->val) {
				cur->next = l1;
				cur = cur->next;
				l1 = l1->next;
			}
			else {
				cur->next = l2;
				cur = cur->next;
				l2 = l2->next;
			}
		}
		if (l1 == NULL) {
			cur->next = l2;
		}
		else {
			cur->next = l1;
		}
		return head->next;
	}

	vector<string> generateParenthesis(int n) {
		vector<string> ss;
		string temp;
		generateParenthesisDFS(ss, n, n, temp);
		for (auto i : ss) cout << i << " ¡£ ";
		vector<string> ans(ss.begin(), ss.end());
		return ans;
	}
	void generateParenthesisDFS(vector<string> &ss, int l, int r, string &temp) {
		if (l == 0 && r == 1) {
			temp += ")";
			ss.emplace_back(temp);
			temp.pop_back();
			return;
		}
		if (l == -1 ) return;
		if (l > r) return;
		if (l == r) {
			temp += "(";
			generateParenthesisDFS(ss, l - 1, r, temp);
			temp.pop_back();
		}
		if (l < r) {
			temp += "(";
			generateParenthesisDFS(ss, l - 1, r, temp);
			temp.pop_back();
			temp += ")";
			generateParenthesisDFS(ss, l, r - 1, temp);
			temp.pop_back();
		}
	}

	ListNode* swapPairs(ListNode* head) {
		ListNode* cur0 = head;
		ListNode* cur1 = head;
		ListNode* cur2 = head;
		if (head == NULL || head->next == NULL) { return head; }
		else {
			head = head->next;
			cur0->next = head->next;
			head->next = cur0;
			cur1 = cur0->next;
		}
		while (cur1 != NULL && cur1->next != NULL) {
			cur2 = cur1->next;
			cur1->next = cur2->next;
			cur0->next = cur2;
			cur2->next = cur1;
			cur0 = cur1;
			cur1 = cur0->next;
		}
		return head;
	}

	int removeDuplicates(vector<int>& nums) {
		int ind, ans, temp;
		ind = 0;
		ans = 0;
		if (nums.size() < 2) return nums.size()-ans;
		temp = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			if (temp == nums[i]) {
				ans++;
			}
			else {
				nums[ind + 1] = nums[i];
				ind++;
				temp = nums[i];
			}
		}
		return nums.size()-ans;
	}

	int removeElement(vector<int>& nums, int val) {
		int ind, ans, temp;
		ind = -1;
		ans = 0;
		if (nums.size() == 0) return 0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != val) {
				nums[ind + 1] = nums[i];
				ind++;
				ans++;
			}
		}
		return ans;
	}

	int strStr(string haystack, string needle) {
		if (haystack.empty()) return -1;
		if (needle.empty()) return 0;
		for (int i = 0; i < haystack.size()-needle.size()+1; i++) {
			if (haystack[i] == needle[0]) {
				int j=0;
				for (j = 0; j < needle.size();j++) {
					if (haystack[i + j] != needle[j]) break;
				}
				if (j == needle.size()) return i;
			}

		}
		return -1;
	}

	int divide(int dividend, int divisor) {
		if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
		int sign = -1;
		if ((dividend < 0 && divisor < 0 || (dividend>0 && divisor >0))) sign = 1;
		long long dvd = labs(dividend);
		long long dvs = labs(divisor);
		int res = 0;
		int pow = 0;
		while (dvd - (dvs << pow) > 0) {
			pow++;
		}
		for (; pow >= 0; pow--) {
			//cout << dvd << " ";
			if (dvd - (dvs << pow) >= 0) {
				dvd -= dvs << pow;
				res += 1 << pow;
				
			}
		}
		
		return sign==1? res:-res;
	}

	void nextPermutation(vector<int>& nums) {
		int vlen = nums.size();
		if (vlen == 1) return;
		int ind1 = vlen - 1;
		while (ind1 > 0 && nums[ind1] <= nums[ind1 - 1] ) {
			ind1--;
		}
		if (ind1 == vlen - 1) {
			swap(nums[vlen - 2], nums[vlen - 1]);
			return;
		}
		if (ind1 == 0) {
			std::reverse(nums.begin(), nums.end());
			return;
		}
		int i;
		for (i = vlen - 1; i >= ind1; i--) { if (nums[i] > nums[ind1 - 1]) break; }
		swap(nums[i], nums[ind1 - 1]);
		std::reverse(nums.begin()+ind1, nums.end());
		return;
	}

private:
	double find_Kth(vector<int>& nums1, int ind1, vector<int>& nums2, int ind2, int k) {
		int len1 = nums1.size();
		int len2 = nums2.size();
		while (k > 1 && ind1 + ind2 < k ) {
			if (ind1 == len1) return nums2[k];
			if (ind2 == len2) return nums1[k];
			int mid1 = (len1 -1 + ind1) / 2;
			int mid2 = (len2 -1 + ind2) / 2;
			if (nums1[mid1] < nums2[mid2]){
				k = k - (mid1 - ind1);
				ind1 = mid1 + 1;
			}
			else if (nums1[mid1]>nums2[mid2]) {
				k = k - (mid2 - ind2);
				ind2 = mid2 + 1;
			}
			else {
				return (nums1[ind1]);
			}
		}
		if (k == 0) {
			return min(nums1[ind1], nums2[ind2]);
		}
		else {
			return max(nums1[ind1], nums2[ind2]);
		}
	}



};



ListNode* createLinkedList(initializer_list<int> lst) {
	auto iter = lst.begin();
	//cout << *iter;
	ListNode* head = new ListNode(*iter++);
	ListNode* cur = head;
	while (iter != lst.end()) {
		cur->next = new ListNode(*iter);
		cur = cur->next;
		//cout << *iter;
		iter++;		
	}
	return head;
}

void printLinkedList(ListNode* head) {
	ListNode* cur = head;
	if (head == NULL) { 
		cout << "empty" << endl;
		return; 
	}
	while (cur != NULL) {
		cout << cur->val << "->";
		cur = cur->next;
	}
}

template<typename T>
void printVector(vector<T> vi) { for (auto i : vi) cout << i << " "; }

int main() {
	int i = 3;
	//cout << i / 2;
	Solution Sol;

	//31. Next Permutation
	vector<int> vi{1};
	Sol.nextPermutation(vi);
	printVector(vi);

	//29. Divide Two Integers
	int ans = Sol.divide(-15, 3);
	cout << ans;

	//28 Implement strStr()
	//int ans = Sol.strStr("abb", "abaaa");
	//cout << ans;

	//27. Remove Element
	//vector<int> vi{ 0,1,2,2,3,0,4,2 };
	//int ans = Sol.removeElement(vi, 2);

	//26. Remove Duplicates from Sorted Array
	//vector<int> vi={ 1,1,2,3,4,4 };
	//int ans = Sol.removeDuplicates(vi);
	//for (auto i : vi) cout << i << "->";
	//cout << ans;

	//24. Swap Nodes in Pairs
	//ListNode* l1 = createLinkedList({ 1, 2, 3, 4,5,6,7,8,9 });
	//ListNode* l2 = Sol.swapPairs(l1);
	//printLinkedList(l2);

	//22. Generate Parentheses
	//vector<string> ans = Sol.generateParenthesis(4);
	
	//21 Merge Two Sorted Lists
	//ListNode* l1 = createLinkedList({ 1,2,3,4 });
	//ListNode* l2 = createLinkedList({ 2,3,4,5 });
	//l1 = Sol.mergeTwoLists(l1, l2);
	//printLinkedList(l1);


	//20 Valid Parentheses
	//string s{"}"};
	//bool paren = Sol.isValid(s);
	//cout << paren;

	//19 Remove Nth Node From End of List
	//ListNode* start = createLinkedList({ 1,2,3,4 });
	//printLinkedList(start);
	//ListNode* after = Sol.removeNthFromEnd(start, 4);
	//printLinkedList(after);

	//184Sum
	//vector<int> vi = {};
	//vector<vector<int>> vvi = Sol.fourSum(vi, 12);

	//17 Letter Combinations of a Phone Number
	//vector<string> vs = Sol.letterCombinations("23");
	
	// 16 3 Sum Closeset
	//vector<int> nums = { -1, 2, 1, -4 };
	//int target = 1;
	//int ans = Sol.threeSumClosest(nums, target);
	//cout << ans;
	//15 3Sum
	//vector<int> vi = { -2,0,3,-1,4,0,3,4,1,1,1,-3,-5,4,0 };
	//vector<vector<int>> vvi = Sol.threeSum(vi);

	//14 Longest Common Prefix
	//vector<string> strs{ "aca","cba" };
	//string s = Sol.longestCommonPrefix(strs);
	//cout << s;

	//13 Roman to Integer
	//int t = Sol.romanToInt("LVIII");
	//cout << t;

	//12 Integer to Roman
	//string s = Sol.intToRoman(58);
	//cout << s;

	//11 Container With Most Water
	//vector<int> height({ 1,8,6,2,5,4,8,3,7 });
	//int ma = Sol.maxArea(height);
	//cout << ma;

	//9 Palindrome Number
	//bool b = Sol.isPalindrome(-121);
	//cout << b;

	//8 String to Integer (atoi)
	//int t = Sol.myAtoi("9223372036854775808");
	//cout << t;

	//7 Reverse Integer
	//int y = Sol.reverse(1534236469);

	// 6 zigzag conversion
	//string s("A");
	//string ans = Sol.convert(s, 2);

	//5 Longest Palindromic Substring
	//string s("babad");
	//string ans = Sol.longestPalindrome(s);

	//4 Median of Two Sorted Arrays//
	//vector<int> num1{ 0,3 ,6,9};
	//vector<int> num2{ 1 };
	//double result = Sol.findMedianSortedArrays(num1, num2);
	//cout << result;
	
	//string s = "abcabcbb";
	//i = Sol.lengthOfLongestSubstring(s);
	//cout << i;

	//2 addTwoNumbers///
	//ListNode* list1;
	//ListNode* list2;
	//ListNode* resultnode;
	//list1 = createLinkedList({ 2,4,3 });
	//list2 = createLinkedList({ 5,6,4 });
	//resultnode = Sol.addTwoNumbers(list1, list2);

	//1 twoSum///
	//vector<int> nums{ 2, 7, 11, 6, 7 };
	//vector<int> result;
	//result = Sol.twoSum(nums, 6);

	cin >> i;
}
#include <iostream>
#include <vector>

using namespace std;


class Solution
{
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        unsigned min_length, max_length;
        vector<int> n1 = nums1, n2 = nums2;
        if(nums1.size() > nums2.size()) {
            min_length = nums2.size();
            max_length = nums1.size();
            n1 = nums2;
            n2 = nums1;

        } else {
            min_length = nums1.size();
            max_length = nums2.size();
        }

        unsigned lb = 0;
        unsigned ub = min_length;
        unsigned i, j;

        for(i = lb; i <= ub; i = (lb + ub)/2) {
            j = (min_length + max_length + 1) / 2 - i;
            cout << "j = " << j << endl;
            if((i == 0 || j == max_length || n1[i-1] <= n2[j]) && (i == min_length || j == 0 || n2[j-1] <= n1[i])) {
                cout << "i " << i << ",j " <<j << endl;
                cout << n2[j-1]<< n1[i] << endl;
                break;
            } else if(i > 0 && n1[i-1] > n2[j]) {
                ub = i - 1;
            } else if(i < min_length && n2[j-1] > n1[i]) {
                lb = i + 1;
            }
        }
        cout << "i = " << i << ", j = " << j <<endl;
        if((min_length + max_length) % 2 == 0) {
            if(i>0 && i<min_length) {
                return (double)(max(n1[i-1], n2[j-1]) + min(n1[i], n2[j])) / 2;
            } else if(i == 0 || i == min_length) {
                return (double) (n2[j-1] + n2[j]) / 2;
            }

        } else {
            return max(n1[i-1], n2[j-1]);
        }
    }
};

class Solution2
{
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        if(nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size();
        int n = nums2.size();
        int imin = 0, imax = m;
        while(imin <= imax) {
            int i = (imin + imax)/2;
            int j = (m+n+1)/2 - i;
            //cout << "i = " << i << ", j = " << j << endl;
            if(i < m && nums2[j-1] > nums1[i]) {
                imin = i + 1;
                //cout << "nums2[j-1] > nums1[i]" << endl;
                continue;
            } else if(i > 0 && nums1[i-1] > nums2[j]) {
                imax = i - 1;
                //cout << "nums1[i-1] > nums2[j]" << endl;
                continue;
            } else {
                int maxLeft = 0;
                if(i == 0) {
                    maxLeft = nums2[j-1];
                } else if(j == 0) {
                    maxLeft = nums1[i-1];
                } else {
                    maxLeft = max(nums1[i-1], nums2[j-1]);
                }
                if((m+n)%2 == 1) {
                    return maxLeft;
                }
                int maxRight = 0;
                if(i == m) {
                    maxRight = nums2[j];
                } else if(j == n) {
                    maxRight = nums1[i];
                } else {
                    maxRight = min(nums1[i], nums2[j]);
                }
                return (maxLeft + maxRight)/2.0;
            }
        }
        return 0.0;
    }
};


int main()
{
    Solution2 s;
    vector<int> nums1 = {1,2,3,4};
    vector<int> nums2 = {5,6,7,8};
    double median;
    median = s.findMedianSortedArrays(nums1, nums2);
    cout << median << endl;

    return 0;
}


import java.util.HashMap;
import java.util.Hashtable;

public class CodeArray {

    public int[] twoSum(int[] nums, int target) {
        int [] elem = new int[2];
        elem[0]  = elem[1] = -1;
        HashMap<Integer,Integer> map = new HashMap<Integer, Integer>();
        for (int i = 0; i<nums.length; i++ ) {
            if (target == 2 * nums[i] && elem[0] < 0 ) {
                elem[0] = i;
                nums[i] = target*2;
            } else if (target == 2 * nums[i] && elem[0] >= 0) {
                elem[1] = i;
                return elem;
            }
        }
        for (int i = 0; i<nums.length; i++ ) {
            map.put(new Integer(nums[i]), new Integer(i));

        }
        for (int i = 0; i < nums.length; i++) {
            int reminder = target - nums[i];
            //System.out.println(nums[i]  +" "+ i +" " + target + " " + reminder);
            if (map.containsKey(reminder)) {
                int r = map.get(reminder) ;
                elem[0] = i<=r ? i:r;
                elem[1] = i>r ? i:r;
                return elem;
            }
        }
        return elem;
    }
    public int[] twoSumV2(int[] nums, int target) {
        int [] elem = new int[2];
        elem[0]  = elem[1] = -1;
        HashMap<Integer,Integer> map = new HashMap<Integer, Integer>();

        for (int i = 0; i<nums.length; i++ ) {
            map.put(new Integer(nums[i]), new Integer(i));
        }
        System.out.println("ola " + map.get(3));
        for (int i = 0; i < nums.length; i++) {
            int reminder = target - nums[i];
            System.out.println(nums[i]  +" "+ i +" " + target + " " + reminder);
            if (map.containsKey(reminder) && map.get(reminder) != i) {

                int r =  map.get(reminder);
                System.out.println(i +" "+ r);
                elem[0] = i<=r ? i:r;
                elem[1] = i>r ? i:r;
                return elem;
            }
        }
        return elem;
    }


    public int lengthOfLongestSubstringV2(String s) {
        Freuency [] freuency = new Freuency[128];
        int max_len = 0;
        int count = 0;
        int space_count = 0;

        String str = s;

        int pos = 0;

        for (int i=0; i< freuency.length;i++ ) {
            freuency[i] = new Freuency();
        }

        for (int i = 0;i <str.length(); i++) {
            pos  = str.charAt(i);
            freuency[pos].freq++;
            count++;
            /*System.out.println(" i " + i +" char "+ str.charAt(i)+ " Count " + count + " max_len " + max_len + " pos " + pos  + " freq " + freuency[pos].freq
                      + " lastpos "  + freuency[pos].lastPos );*/
            if (freuency[pos].freq > 1 ) {
                if (count > max_len ) {
                    max_len = count - 1;

                }
                count = 0;
                // i will increase at the end of loop
                i = freuency[pos].lastPos;
                // reset frequerncy
                for (int j =0 ;j< freuency.length; j++) {
                    freuency[j].freq = 0;
                    freuency[j].lastPos = 0;
                }
                continue;
            }
            freuency[pos].lastPos = i;
        }
        if (count >= max_len + 1)
            max_len = count;
        return max_len + space_count;

    }

    public int lengthOfLongestSubstringV1(String s) {
        HashMap <Character,Integer> map= new HashMap<Character,Integer>();
        int n = s.length();
        int j = 0;
        int max_len = 0;
        int i = 0;
        for (i = 0; j<n; j++) {
            if (map.containsKey(s.charAt(j))) {
                i = Math.max(map.get(s.charAt(j)),i);
            }
            max_len = Math.max(max_len,j-i+1);
            map.put(s.charAt(j),j+1);
        }
        return max_len;

    }

    // this is the best solutions
    public int lengthOfLongestSubstring(String s) {
        int [] index = new int [128];
        int n = s.length();
        int j = 0;
        int max_len = 0;
        int i = 0;
        for (i =0; j < n; j++) {
            i = Math.max(index[s.charAt(j)],i);
            max_len = Math.max(max_len,j-i+1);
            index[s.charAt(j)]= j + 1 ;
        }
        return max_len;
    }

    public class Freuency {
        public int freq;
        public int lastPos;
    }

    public double findMedianSortedArraysV2(int[] nums1, int[] nums2) {


        if (nums1.length > nums2.length){
            return findMedianSortedArraysV2(nums2,nums1);
        }
        int x = nums1.length; // length of array x (nums1 here)
        int y = nums2.length; // length of array y (nums2 here)

        int start = 0;
        int end = x;

        while (start <= end) {
            int partitionX = (start + end)/2;
            int partitionY = (x+y+1)/2 - partitionX;

            // if partitionX has shifted so much to the left then use -Infinity
            // if partitionX has shifte so much to the right then us +Infinity
            // In both case the partition left or right of array X would be empty
            int maxLeftX = partitionX == 0 ? Integer.MIN_VALUE : nums1[partitionX-1];
            int minRightX = partitionX == x ? Integer.MAX_VALUE : nums1[partitionX];
            // if partitionY has shifted so much to the left then use -Infinity
            // if partitionY has shifte so much to the right then us +Infinity
            // In both case the partition left or right of array Y would be empty
            int maxLeftY = partitionY == 0 ? Integer.MIN_VALUE : nums2[partitionY-1];
            int minRightY = partitionY == y ? Integer.MAX_VALUE : nums2[partitionY];

            if (maxLeftX <= minRightY && maxLeftY <= minRightX ) {
                // we have partitioned the array in the right place
                // if total length is even get the avg of the value
                if ( (x+y)%2 == 0 ) {
                     return (double)((Math.max(maxLeftX,maxLeftY) + Math.min(minRightX,minRightY))/2.0);
                }
                else {
                    return Math.max(maxLeftX,maxLeftY);
                }
            } else if (maxLeftX > minRightY) {
                end = partitionX - 1;
            } else {
                start = partitionX + 1;
            }


        }
     throw new IllegalArgumentException();
    }
    public double findMedianSortedArrays(int input1[], int input2[]) {
        //if input1 length is greater than switch them so that input1 is smaller than input2.
        if (input1.length > input2.length) {
            return findMedianSortedArrays(input2, input1);
        }
        int x = input1.length;
        int y = input2.length;

        int low = 0;
        int high = x;
        while (low <= high) {
            int partitionX = (low + high)/2;
            int partitionY = (x + y + 1)/2 - partitionX;

            //if partitionX is 0 it means nothing is there on left side. Use -INF for maxLeftX
            //if partitionX is length of input then there is nothing on right side. Use +INF for minRightX
            int maxLeftX = (partitionX == 0) ? Integer.MIN_VALUE : input1[partitionX - 1];
            int minRightX = (partitionX == x) ? Integer.MAX_VALUE : input1[partitionX];

            int maxLeftY = (partitionY == 0) ? Integer.MIN_VALUE : input2[partitionY - 1];
            int minRightY = (partitionY == y) ? Integer.MAX_VALUE : input2[partitionY];

            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                //We have partitioned array at correct place
                // Now get max of left elements and min of right elements to get the median in case of even length combined array size
                // or get max of left for odd length combined array size.
                if ((x + y) % 2 == 0) {
                    return ((double)Math.max(maxLeftX, maxLeftY) + Math.min(minRightX, minRightY))/2;
                } else {
                    return (double)Math.max(maxLeftX, maxLeftY);
                }
            } else if (maxLeftX > minRightY) { //we are too far on right side for partitionX. Go on left side.
                high = partitionX - 1;
            } else { //we are too far on left side for partitionX. Go on right side.
                low = partitionX + 1;
            }
        }

        //Only we we can come here is if input arrays were not sorted. Throw in that scenario.
        throw new IllegalArgumentException();
    }
    public String longestPalindrome(String s) {
        int maxLen = Integer.MIN_VALUE;
        int start = 0;
        int end = 0;
        int len = 0;
        int len1 = 0;
        int len2 = 0;

        if(s.length() == 0) {
            return "";
        }

        for (int i = 0; i < s.length(); i++) {
            len1 = palindromeLen(s, i, i);
            len2 = palindromeLen(s, i, i+1);
            len = Math.max(len1,len2);
            if (len > maxLen) {
                maxLen = len;
                start = i - (len-1)/2;
                end = i + len/2;
            }


        }
        return s.substring(start,end+1);

    }
    public int palindromeLen(String s, int l , int r) {
        int len = 0;
        while( l>=0 && r<s.length()
                && s.charAt(l) == s.charAt(r)) {
            len = r-l +1;
            l--;
            r++;
        }
        return len;

    }

    public String longestPalindromeV2(String s) {
        int maxLen = Integer.MIN_VALUE;
        int start = 0;
        int end = 0;
        int count = 0;
        boolean first = true;
        boolean is_repeat = false;
        boolean isPalindrome = false;

        if(s.length() == 0) {
            return "";
        }
        if (s.length() == 1 || s.length() == 2) {
            return s;
        }
        int midL = 0;
        int midR = 0 ;
        for (int i = 2; i < s.length(); i++) {
            System.out.println(s.charAt(i) + " " + i +" ");
            if ((s.charAt(i) == s.charAt(i-1) || s.charAt(i) == s.charAt(i-2))
                    && (isPalindrome == false || is_repeat) ) {
                //isPalindrome = true;
                if (s.charAt(i) == s.charAt(i-1) &&
                        s.charAt(i) != s.charAt(i-2)) {
                    count = 2;
                    midR = i;
                    midL = i-1;
                    isPalindrome = true;
                    is_repeat = true;
                } else if (s.charAt(i) == s.charAt(i-2) &&
                        s.charAt(i) != s.charAt(i-1)) {
                    count = 3;
                    midR = midL = i-1;
                    isPalindrome = true;

                } else {

                    is_repeat = true;
                    if (first) {
                        count = 3;
                        first = false;
                    }
                    else
                        count++;
                    System.out.println("repeat " + count);

                }
                continue;
            }
            if (is_repeat) {
                isPalindrome = true;
                is_repeat = false;
                if (count%2 ==0 ) {
                    midR = i-1;
                    midL = i - count;
                }
            }

            if (isPalindrome) {
                int x = i - midR;
                System.out.println(x + ":(" + midL+","+midR +") "+ count + " "+ maxLen);
                // this char is also part of palindrome
                int left = midL - x ;
                int right = midR + x;
                if ((left >= 0 && right < s.length())
                        && s.charAt(left) == s.charAt(right)){
                    count += 2;
                    if (maxLen < count) {
                        maxLen = count;
                        if (midL == midR) {
                            start = midL - count/2;
                            end = midL + count/2 +1; //adding +1 so that end points to endindex+1 for str.substing()

                        } else {
                            start = midL - count/2 +1;
                            end = midR + count/2;
                        }
                    }
                } else { // this char is not part of palindrome

                    count = 0;
                    isPalindrome = false;
                }
                System.out.println("st "+ start + " end "+end + " " + isPalindrome);
            }

        }
        if (s.length() == 3 && isPalindrome)
            return s;
        return s.substring(start,end);

    }
}

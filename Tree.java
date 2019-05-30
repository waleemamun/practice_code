import java.awt.image.AreaAveragingScaleFilter;
import java.util.ArrayList;
import java.util.LinkedList;

public class Tree {
    public TreeNode root;
    public Tree (int rootVal){
        root = new TreeNode(rootVal);
    }
    public Tree () {
        root = new TreeNode(Integer.MIN_VALUE); // creating a tree but the root value is not init
    }

    public TreeNode getRoot() {
        return root;
    }

    public void setRoot(TreeNode root) {
        this.root = root;
    }

    public void createBinaryTree (int arr[]) {
        if (arr.length == 0) {
            System.out.println("Array size zero");
        }
        int mid = arr.length/2;
        root.data = arr [mid];
        root.leftChild = createBinaryTreeRecurse(0, mid-1, arr);
        root.rightChild = createBinaryTreeRecurse(mid+1, arr.length-1,arr);

    }

    public TreeNode createBSTree (int low , int high, int arr []){
        if (low > high) {
            return null;
        }
        int mid = (low + high)/2;
        TreeNode node = new TreeNode(arr[mid]);
        System.out.println("Creating node "+ node.data + "[" + low +"," + high + "] " + mid);
        node.leftChild = createBSTree(low, mid-1, arr);
        node.rightChild = createBSTree(mid+1, high, arr);
        return node;
    }

    private TreeNode createBinaryTreeRecurse (int low, int high, int arr []) {
        if (low > high) {
            return null;
        }
        int mid = (low + high)/2;
        TreeNode node = new TreeNode(arr[mid]);
        System.out.println("Creating node "+ node.data + "[" + low +"," + high + "] " + mid);
        node.leftChild = createBinaryTreeRecurse(low, mid-1, arr);
        node.rightChild = createBinaryTreeRecurse(mid+1, high, arr);
        return node;
    }
    // return Integer.MIN_VALUE if not balanced
    public int checkBalanced (TreeNode node) {

        if (node == null) {
            return 0;
        }
        int leftHeight = checkBalanced(node.leftChild);
        if (leftHeight == Integer.MIN_VALUE)
            return Integer.MIN_VALUE;
        int rightHeight = checkBalanced(node.rightChild);
        if (rightHeight == Integer.MIN_VALUE)
            return Integer.MIN_VALUE;

        if (Math.abs(leftHeight-rightHeight) > 1) {
            return Integer.MIN_VALUE;
        } else
            return (1 + Math.max(leftHeight,rightHeight));
    }

    public void inOrderTraversal (TreeNode node) {
        if ( node != null) {
            inOrderTraversal(node.leftChild);
            System.out.print(node.data + " ");
            inOrderTraversal(node.rightChild);
        }
    }

    public void preOrderTraversal (TreeNode node) {
        if (node != null) {
            System.out.print(node.data + " ");
            preOrderTraversal(node.leftChild);
            preOrderTraversal(node.rightChild);
        }
    }

    public TreeNode search(int data, TreeNode node) {
        if (node == null) {
            System.out.println("Data not found");
            return null;
        }
        if (data == node.data) {
            return node;
        }
        else if (data < node.data) {
            return search(data, node.leftChild);
        } else {
            return search(data, node.rightChild);
        }
    }

    public TreeNode searchBiggest (TreeNode node) {
        if (node == null) {
            return null;
        }
        if (node.rightChild == null)
            return node;
        return searchBiggest(node.rightChild);

    }

    public TreeNode searchSmallest (TreeNode node) {
        if (node == null) {
            return null;
        }
        if (node.leftChild == null)
            return node;
        return searchSmallest(node.leftChild);

    }

    public int validateBST (TreeNode node, int leftBoundary , int rightBoundary) {
        if (node == null)
            return 1;
        if (node.data <= rightBoundary && node.data > leftBoundary) {

            return (validateBST(node.leftChild, leftBoundary, node.data) &
                          validateBST(node.rightChild, node.data, rightBoundary));
        } else
            return 0;

    }

    // This is an utility method to weave two list first and second in such a way
    // that the order of the element in each list remains the same
    // for example to weave list (1,2) and (3,4) we get the following output observe the order remains the same
    // 1 2 3 4
    // 1 3 2 4
    // 1 3 4 2
    // 3 1 2 4
    // 3 1 4 2
    // 3 4 1 2


    public static void weaveList (LinkedList<Integer> first,
                           LinkedList<Integer> second,
                           LinkedList<Integer> prefix,
                           ArrayList<LinkedList<Integer>> results) {

        // if one of the list is empty we merge the list with the clone of prefix list
        // here the clone is use so that we only work on the clone prefix for this call and the original prefix does not
        // get modified in the subsequent recursive call
        if (first.size() == 0 || second.size() == 0) {
            LinkedList<Integer> mergeList = (LinkedList<Integer>) prefix.clone();
            mergeList.addAll(first);
            mergeList.addAll(second);
            results.add(mergeList);
            return;

        }

        // remove one entry from the first list and add it to the prefix to call the weaveList
        // after that we restore both prefix and first for the subsequent recursive call
        int headFirst = first.removeFirst();
        prefix.addLast(headFirst);
        weaveList(first, second, prefix, results);
        prefix.removeLast();
        first.addFirst(headFirst);

        // remove one entry from the second list and add it to the prefix to call the weaveList
        // after that we restore both prefix and second for the subsequent recursive call
        int headSecond = second.removeFirst();
        prefix.addLast(headSecond);
        weaveList(first, second, prefix, results);
        prefix.removeLast();
        second.addFirst(headSecond);

    }
    // If this tree contains the tree tr then the pre order traversal
    // for this tree will contain the preorder traversal of tree tr,
    // so the string representing the trversal for tree tr would be a substring of this tree's traversal
    public boolean contains(Tree tr) {
        StringBuilder str1 = new StringBuilder();
        StringBuilder str2 = new StringBuilder();

        preOrderTraversalString(getRoot(),str1);
        preOrderTraversalString(tr.getRoot(),str2);

        return str1.toString().indexOf(str2.toString()) != -1;
    }
    public void preOrderTraversalString(TreeNode node, StringBuilder str){
        if (node == null) {
            str.append("X ");
        } else {
            str.append(node.data + " ");
            preOrderTraversalString(node.leftChild,str);
            preOrderTraversalString(node.rightChild,str);

        }

    }
    public TreeNode inOrderPredecessorWithoutParent (TreeNode node) {
        if (node.leftChild != null) {
            return searchBiggest(node.leftChild);
        }
        TreeNode pred = null;
        TreeNode rt = root;

        while (rt != null) {
            if (node.data < rt.data) {
                rt = rt.leftChild;
            } else if (node.data > rt.data) {
                pred = rt;
                rt = rt.rightChild;
            } else {
                break;
            }
        }
        return pred;
    }

    public TreeNode inOrderSuccesorWithParent (TreeNode node) {
        if (node.rightChild != null) {
            return searchSmallest(node.rightChild);
        }
        TreeNode pnode = node.parent;
        while(pnode != null && pnode.rightChild == node) {
            pnode = pnode.parent;
            node = node.parent;
        }
        return pnode;
    }
    public TreeNode inOrderSuccessorWithoutParent (TreeNode node) {
        TreeNode rt = root;
        TreeNode succ = null;

        if (node.rightChild != null) {
            return searchSmallest(node.rightChild);
        }

        while (rt != null) {
            if (node.data < rt.data) {
                succ = rt;
                rt = rt.leftChild;
            } else if (node.data > rt.data) {
                rt = rt.rightChild;
            } else
                break;
        }
        return succ;

    }

    public void levelOrderTraversalAdd2List () {
        ArrayList<LinkedList<TreeNode>> listArray = new ArrayList<>();
        int level = 0;
        LinkedList<TreeNode> list  = new LinkedList();
        list.add(root);
        listArray.add(level,list);

        while (true) {
            list = new LinkedList<>();
            for (int i = 0; i < listArray.get(level).size(); i++) {
                TreeNode node = (TreeNode) listArray.get(level).get(i);
                if (node.leftChild != null)
                    list.add(node.leftChild);
                if (node.rightChild != null)
                    list.add(node.rightChild);
            }
            if (list.size() == 0) {
                break;
            }
            level++;
            listArray.add(level,list);

        }

    }
    public boolean covers (int data, TreeNode node) {
        if (node == null) {
            return false;
        }
        if (node.data == data)
            return true;
        else
            return covers(data, node.leftChild) | covers(data, node.rightChild);
    }
    public TreeNode commonAncestor(TreeNode nodeA, TreeNode nodeB ) {
        TreeNode root = this.root;
        if (nodeA == null || nodeB == null) {
            return root;
        }
        if (isAncestor(nodeA , nodeB))
            return nodeA;
        if (isAncestor(nodeB,nodeA)) {
            return nodeB;
        }
        return commonAncestor(root, nodeA.data, nodeB.data);

    }
    private TreeNode commonAncestor(TreeNode ancestor, int nodeAData, int nodeBData) {
        boolean aOnLeft = covers(nodeAData, ancestor.leftChild);
        boolean bOnleft = covers(nodeBData, ancestor.leftChild);
        //System.out.println("aOnLeft " + aOnLeft + " bOnleft " + bOnleft);

        if (aOnLeft != bOnleft)
            return ancestor;
        return aOnLeft ? commonAncestor(ancestor.leftChild, nodeAData, nodeBData) :
                commonAncestor(ancestor.rightChild, nodeAData, nodeBData);


    }
    public boolean isAncestor (TreeNode ancestor, TreeNode child) {
        TreeNode node = ancestor;
        return covers(child.data, ancestor.leftChild) | covers(child.data, ancestor.rightChild);
    }

    public boolean getPathFromNode (ArrayList<Integer> path, TreeNode src, TreeNode dest) {
        if (src == null)
            return false;

        if (src.data == dest.data) {
            path.add(dest.data);
            return true;
        }
        if ( getPathFromNode(path,src.leftChild, dest) ||
                getPathFromNode(path, src.rightChild, dest)) {
            path.add(src.data);
            return true;
        } else {
            return false;
        }
    }
    /*
     *  This will give the common ancestor of two nodes using the getPathFromNode method
     *  If we can get the path from root to nodeA and nodeB then the point where the path diverges
     *  is the first common ancestor
     * */
    public TreeNode getCommonAncestor(TreeNode nodeA, TreeNode nodeB) {

        if (nodeA == null || nodeB == null)
            return getRoot();

        TreeNode ancestor = null;
        ArrayList<Integer> pathNodeA = new ArrayList<>();
        ArrayList<Integer> pathNodeB = new ArrayList<>();

        if (getPathFromNode(pathNodeA , getRoot(), nodeA) &&
                getPathFromNode(pathNodeB, getRoot(), nodeB)) {

            int i = pathNodeA.size() - 1;
            int j = pathNodeB.size() - 1 ;
            while (i>= 0 && j >= 0 &&
                    (pathNodeA.get(i) == pathNodeB.get(j))) {
                i--;
                j--;
            }
            ancestor = search(pathNodeA.get(i+1),getRoot());
        } else {
            System.out.println("One of the node is not in the tree");
        }
        return ancestor;
    }

}

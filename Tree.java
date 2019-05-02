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
}

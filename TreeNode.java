import java.util.ArrayList;

public class TreeNode {
    int data;
    TreeNode leftChild;
    TreeNode rightChild;
    ArrayList<TreeNode> listOfChild; //non binary tree case
    public TreeNode( int val) {
        data = val;
        leftChild = null;
        rightChild = null;
    }
}

import java.util.ArrayList;

public class Solutions {

    int grid [][]  = {{0, 0, 0, 0},
                      {0, 1, 0, 1},
                      {0, 1, 0, 1},
                      {0, 0, 0, 2}};
    public class Path{
        int i;
        int j;
        public Path(int i , int j){
            this.i = i;
            this.j= j;
        }
    }
    public void towerOfHanoi(int nDisk, int srcPeg, int destPeg, int midPeg) {

        if (nDisk == 1 ) {
            System.out.println("Move disk " +nDisk + " from "+ srcPeg +" to "+ destPeg);
            return;
        }
        towerOfHanoi(nDisk-1,srcPeg,midPeg,destPeg);
        System.out.println("Move disk " +nDisk + " from "+ srcPeg +" to "+ destPeg);
        towerOfHanoi(nDisk-1,midPeg,destPeg,srcPeg);


    }

    public void robotMove (ArrayList<Path>  moveList , int i , int j) {

        if( i < grid[0].length && j < grid.length ) {
            if (grid[i][j] == 1) {
                return;
            } else if (grid[i][j] == 2) {
                // reached destination print the path
                System.out.println("Reached dest");
                for (int ix = 0; ix<moveList.size(); ix++) {
                    System.out.print("(" + moveList.get(ix).i +"," + moveList.get(ix).j+") ->");
                }
                System.out.println("("+i + "," +j+ ")");
            } else {

                moveList.add(new Path(i,j));
                //move right
                ArrayList<Path> right = (ArrayList<Path>) moveList.clone();
                ArrayList<Path> down = (ArrayList<Path>) moveList.clone();
                robotMove(right,i+1, j);
                robotMove(down, i,j+1);

            }
        }
    }

    public int fibonacci (int n) {
        if (n == 0 || n == 1  || n==2){
            return 1;
        }
        return fibonacci(n-1) + fibonacci(n-2);
    }
    public String convert(String s, int numRows) {

        StringBuilder [] sbArray = new StringBuilder[numRows];
        StringBuilder output = new StringBuilder();
        if (numRows == 1)
            return s;
        // init the String array
        for (int i = 0; i < numRows ; i++) {
            sbArray[i] = new StringBuilder();
        }
        int midCharsCount = numRows - 2;
        int rows = 0;
        boolean isVertical = true;
        for (int i = 0; i < s.length(); i++) {

            if (rows == 0) {
                isVertical = true;
            }
            if (rows == numRows) {
                rows-=2;
                if (rows != 0)
                    isVertical = false;
            }
            System.out.println("char "+s.charAt(i) + "  rows " + rows );
            sbArray[rows].append(s.charAt(i));
            if (isVertical == true && rows < numRows) {
                rows++;
            }
            if (isVertical == false && rows > 0 ) {
                rows--;
            }

        }

        for (int i = 0; i < sbArray.length; i++) {
            output.append(sbArray[i]);
        }

        return output.toString();
    }
}

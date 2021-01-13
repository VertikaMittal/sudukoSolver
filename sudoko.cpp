class Solution {
public:
    vector<unordered_set<int>> rowNumbers;
    vector<unordered_set<int>> colNumbers;
    vector<unordered_set<int>> boxNumbers;
    vector<vector<int>> mBoard;
    
    void solveSudoku(vector<vector<char>>& board) {
        /*
        Store numbers row-wise, column-wise and box-wise.
        Then do recursion (backtracking).
        During recursion, we can obtain the possibilities for a
        cell quickly by filtering out the stored numbers in that row, column, box.
        */
        
        rowNumbers.resize(9);
        colNumbers.resize(9);
        boxNumbers.resize(9);        
        mBoard = vector<vector<int>>(9, vector<int>(9, 0));
        
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {                                
                if (board[r][c] == '.') continue;
                
                int num = board[r][c] - '0';
                mBoard[r][c] = num;                
                int bid = getBoxId(r,c);
                rowNumbers[r].insert(num);
                colNumbers[c].insert(num);
                boxNumbers[bid].insert(num);
            }
        }
        
        
        // Backtrack:
        helper(0);
        
        // Generate char board again
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {                                
                board[r][c] = '0' + mBoard[r][c];
            }                
        }
    }
    
    // Backtracking:
    bool helper(int cellIdx) {
        if (cellIdx >= 81) {
            return true;
        }
        int r = cellIdx / 9;
        int c = cellIdx % 9;
        int bid = getBoxId(r,c);
        
        if (mBoard[r][c] != 0) {    // already filled
            return helper(cellIdx+1);
        }
        
        unordered_set<int> possibilities;
        for (int num = 1; num <= 9; num++)
            if (!rowNumbers[r].count(num) && !colNumbers[c].count(num) && !boxNumbers[bid].count(num))
                possibilities.insert(num);
                
        for (int num : possibilities) {
            mBoard[r][c] = num;
            rowNumbers[r].insert(num);
            colNumbers[c].insert(num);
            boxNumbers[bid].insert(num);
            
            bool check = helper(cellIdx+1);
            if (check) return true; // Means the board got solved down the recursion tree.
            
            rowNumbers[r].erase(num);
            colNumbers[c].erase(num);
            boxNumbers[bid].erase(num);
            mBoard[r][c] = 0;
        }
        
        return false;
    }
    
    int getBoxId(int r, int c) {
        int rid = r / 3;
        int cid = c / 3;
        return rid * 3 + cid;            
    }
};

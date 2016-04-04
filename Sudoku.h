using namespace std;


class Sudoku{
public:
    Sudoku();
    void giveQuestion();
    void readIn();
    void solve();
    void changeNum(int a, int b);
    void changeRow(int a, int b);
    void changeCol(int a, int b);
    void rotate(int n);
    void flip(int n);
    void transform();
    int nextblank(int blank);
    bool ini_check();
    int pre();
    bool check(int blank);
    void change();
    void output(bool trueans);
    static const int sudokusize=81;
private:
    int fill;
    int map[sudokusize];
    int ans[sudokusize];
    int filled[sudokusize];
    int arr[9][9];
    int blank;
};

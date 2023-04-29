void movexy(const int paddingLeft, const int paddingTop) {
    if (paddingTop < 0) {
        printf("\033[%dA", (-paddingTop));// MOVE UP
    } else if (paddingTop > 0) {
        printf("\033[%dB", (paddingTop));// MOVE DOWN
    }
    if (paddingLeft < 0) {
        printf("\033[%dD", (-paddingLeft));// MOVE LEFT
    } else if (paddingLeft > 0) {
        printf("\033[%dC", (paddingLeft));// MOVE RIGHT
    }
}
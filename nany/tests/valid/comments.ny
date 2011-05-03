# This test checks for comment recognition
program Comments;

implementation

# Simple comment
function main: int
{
    # Comment in function
    return 0;

    #* Spreading comment
    More commented stuff
    More and more ... and stop *#
}

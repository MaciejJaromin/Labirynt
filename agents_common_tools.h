#ifndef AGENTS_COMMON_TOOLS_H_INCLUDED
#define AGENTS_COMMON_TOOLS_H_INCLUDED

int rotate_direction_clockwise(int direction, int rotation_clockwise);
inline int rotate_direction_counterclockwise(int direction, int rotation_counterclockwise)
{
    return rotate_direction_clockwise(direction,-rotation_counterclockwise);
}
int rotate_direction_clockwise(int direction);
int rotate_direction_counterclockwise(int direction);

template <typename T, int SIZE>
class rotated_view_of_square_matrix
{
    T (*items)[SIZE];
    int rotation;
public:
    rotated_view_of_square_matrix(T (*items)[SIZE]):items(items),rotation(0)
    {}
    void rotate_clockwise()
    {
        rotation = (rotation + 1) % 4;
    }
    T& get(int y,int x)
    {
        // y points down
        // x points right
        for(int i=0;i<rotation;++i)
        {
            int real_y = SIZE-1-x;
            int real_x = y;
            y = real_y;
            x = real_x;
        }
        return items[y][x];
    }
};

#endif // AGENTS_COMMON_TOOLS_H_INCLUDED

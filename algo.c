#include <math.h>

typedef struct      s_data
{
    int     color;
    void    *mlx;
    void    *win;
}                   t_data;

typedef struct      s_pt
{
    int     x;
    int     y;
}                   t_pt;

int ft_plot(t_data *data, t_pt *pt)
{
    mlx_pixel_put(data->mlx, data->win, pt->x, pt->y, data->color);
}

// fractional part of x
double ft_fpart(double x)
{
    if (x < 0)
        return (1 - (x - (double)(int)x));
    return (x - (double)(int)x);
}

double ft_rfpart(double x)
{
    return (1 - ft_fpart(x));
}

////////////////////////////////////////////////////////////////////////////////
//
// #include <stdio.h>
//
// int main(void)
// {
//     double a = 1.6;
//     double b = ft_fpart(a);
//     double c = ft_rfpart(a);
//
//     printf("%lf, %lf, %lf\n", a, b, c);
//     return 0;
// }
//
////////////////////////////////////////////////////////////////////////////////

void ft_swaps(int steep, t_data *data, t_pt *pt1, t_pt *pt2)
{
    int temp;

    if(steep)
    {
        temp = pt1->x;
        pt1->x = pt1->y;
        pt1->y = temp;
        temp = pt2->x;
        pt2->x = pt2->y;
        pt2->y = temp;
    }
    if (pt1->x > pt2->x)
    {
        temp = pt1->x;
        pt1->x = pt2->x;
        pt2->x = temp;
        temp = pt1->y;
        pt1->y = pt2->y;
        pt2->y = temp;
    }
}

void drawLine(t_data *data, t_pt pt1, t_pt pt2)
{
    int steep;
    int dx;
    int dy;
    double gradient;
    int xend;
    int yend;

    steep = abs(pt1->y - pt0->y) > abs(pt1->x - pt0->x);

    ft_swaps(steep, data, pt1, pt2);

    dx = pt2->x - pt1->x;
    dy = pt2->y - pt1->y;
    gradient = (double)dy/dx;

    // handle first endpoint
    xend = pt1->x;
    yend = pt1->y + gradient * (xend - pt1->x);
    xgap = rfpart(pt1->x + 0.5);
    xpxl1 = xend; // this will be used in the main loop
    ypxl1 = ipart(yend);

    if(steep)
    {
        plot(ypxl1,   xpxl1, rfpart(yend) * xgap);
        plot(ypxl1+1, xpxl1,  fpart(yend) * xgap);
    }
    else
    {
        plot(xpxl1, ypxl1  , rfpart(yend) * xgap)
        plot(xpxl1, ypxl1+1,  fpart(yend) * xgap)
    }
    intery := yend + gradient // first y-intersection for the main loop

    // handle second endpoint
    xend := round(x1)
    yend := y1 + gradient * (xend - x1)
    xgap := fpart(x1 + 0.5)
    xpxl2 := xend //this will be used in the main loop
    ypxl2 := ipart(yend)
    if(steep)
    {
        plot(ypxl2  , xpxl2, rfpart(yend) * xgap);
        plot(ypxl2+1, xpxl2,  fpart(yend) * xgap);
    }
    else
    {
        plot(xpxl2, ypxl2,  rfpart(yend) * xgap);
        plot(xpxl2, ypxl2+1, fpart(yend) * xgap);
    }

    // main loop
    if steep then
        for x from xpxl1 + 1 to xpxl2 - 1 do
           begin
                plot(ipart(intery)  , x, rfpart(intery))
                plot(ipart(intery)+1, x,  fpart(intery))
                intery := intery + gradient
           end
    else
        for x from xpxl1 + 1 to xpxl2 - 1 do
           begin
                plot(x, ipart(intery),  rfpart(intery))
                plot(x, ipart(intery)+1, fpart(intery))
                intery := intery + gradient
           end
    end if
end function

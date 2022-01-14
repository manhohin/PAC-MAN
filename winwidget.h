#ifndef WINWIDGET_H
#define WINWIDGET_H
#include <QPixmap>
#include <QWidget>

class WinWidget : public QWidget
{
public:
    WinWidget(QWidget *parent = nullptr);
    ~WinWidget();
    WinWidget(const WinWidget &) = delete;
    WinWidget &operator=(const WinWidget &) = delete;
    void set_winner(int i);
    int winner;

protected:
    virtual void paintEvent(QPaintEvent *event) override;

    void to_display_coordinates(int x, int y, int &dispx, int &dispy);

    // Obtain the 'real' coordinates from the display coordinates
    void to_real_coordinates(int dispx, int dispy, int &x, int &y);

    // Obtain the coordinates of the grid (2D array index) from display coordinates
    void obtain_grid_coordinates(int dispx, int dispy, int &x, int &y);

    // Obtain the coordinates of the grid (2D array index) from real coordinates
    void obtain_grid_coordinates_from_real(int rx, int ry, int &x, int &y);

    void drawLine(QPainter &paint, int x1, int y1, int x2, int y2);
    void drawPixmap(QPainter &paint, int x, int y, int w, int h, const QPixmap &);
    void fillRect(QPainter &paint, int x, int y, int w, int h, const QBrush &);
};

#endif // WINWIDGET_H

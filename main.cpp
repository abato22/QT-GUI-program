#include<QApplication>
#include<QLabel>
#include<QMainWindow>
#include<QMouseEvent>
#include<QMessageBox>
#include<QAction>
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include<QFileDialog>
#include<QKeyEvent>
#include<QTextStream>
#include<QRect>
#include<QPoint>
#include<QDataStream>
#include<QFile>

class MyMainWindow : public QMainWindow {
public:
    MyMainWindow();
    void mousePressEvent(QMouseEvent*event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void paintEvent(QPaintEvent*event)override;
    void keyPressEvent(QKeyEvent*event)override;
    void FileSaveAsMenu();
    void FileOpenMenu();
    QLabel* MyLabel;
    QMenu* FileMenu;
    QAction* FileSaveAs;
    QAction* FileOpen;
    QRect rekt;
    QPen pen;
};

MyMainWindow::MyMainWindow() {
    MyLabel = new QLabel(this);
    MyLabel->setText("Hello World!");
    rekt.setTopLeft(rekt.topLeft());
    rekt.setBottomRight(rekt.bottomRight());

    FileSaveAs = new QAction(tr("&Save As..."), this);
    FileSaveAs->setShortcut(tr("CTRL+S"));
    connect(FileSaveAs, &QAction::triggered, this, &MyMainWindow::FileSaveAsMenu);
    FileOpen = new QAction(tr("&Open..."), this);
    FileOpen->setShortcut(tr("CTRL+O"));
    connect(FileOpen, &QAction::triggered, this, &MyMainWindow::FileOpenMenu);
    FileMenu = menuBar()->addMenu(tr("&File"));
    FileMenu->addAction(FileSaveAs);
    FileMenu->addAction(FileOpen);
    FileMenu = menuBar()->addMenu(tr("&Edit"));
    FileMenu = menuBar()->addMenu(tr("&Mode"));
}

void MyMainWindow::mousePressEvent(QMouseEvent*event){
    if(event->button() == Qt::LeftButton){
        rekt.setTopLeft(event->pos());
        rekt.setBottomRight(event->pos());
        MyLabel->move(event->pos());
    }
}

void MyMainWindow::mouseMoveEvent(QMouseEvent*event){
    if(event->type() == QEvent::MouseMove){
        rekt.setBottomRight(event->pos());
    }
    update();
}

void MyMainWindow::mouseReleaseEvent(QMouseEvent*event){
    if(event->type() == QEvent::MouseButtonRelease){
        if(rekt.top() > rekt.bottom() && rekt.right() < rekt.left()){
            MyLabel->move(rekt.bottomRight());
        }
        if(rekt.top() > rekt.bottom() && rekt.right() > rekt.left()){
            MyLabel->move(rekt.bottomLeft());
        }
        if(rekt.top() < rekt.bottom() && rekt.right() < rekt.left()){
            MyLabel->move(rekt.topRight());
        }
        if(rekt.top() < rekt.bottom() && rekt.right() > rekt.left()){
            MyLabel->move(rekt.topLeft());
        }
    }
    update();
}

void MyMainWindow::keyPressEvent(QKeyEvent*event){
    if(event->key()==Qt::Key_Up){
        rekt.translate(0,-30);
        if(rekt.top() > rekt.bottom() && rekt.right() < rekt.left()){
            MyLabel->move(rekt.bottomRight());
        }
        if(rekt.top() > rekt.bottom() && rekt.right() > rekt.left()){
            MyLabel->move(rekt.bottomLeft());
        }
        if(rekt.top() < rekt.bottom() && rekt.right() < rekt.left()){
            MyLabel->move(rekt.topRight());
        }
        if(rekt.top() < rekt.bottom() && rekt.right() > rekt.left()){
            MyLabel->move(rekt.topLeft());
        }
    }
    if(event->key()==Qt::Key_Down){
        rekt.translate(0,30);
        if(rekt.top() > rekt.bottom() && rekt.right() < rekt.left()){
            MyLabel->move(rekt.bottomRight());
        }
        if(rekt.top() > rekt.bottom() && rekt.right() > rekt.left()){
            MyLabel->move(rekt.bottomLeft());
        }
        if(rekt.top() < rekt.bottom() && rekt.right() < rekt.left()){
            MyLabel->move(rekt.topRight());
        }
        if(rekt.top() < rekt.bottom() && rekt.right() > rekt.left()){
            MyLabel->move(rekt.topLeft());
        }
    }
    if(event->key()==Qt::Key_Right){
        rekt.translate(30,0);
        if(rekt.top() > rekt.bottom() && rekt.right() < rekt.left()){
            MyLabel->move(rekt.bottomRight());
        }
        if(rekt.top() > rekt.bottom() && rekt.right() > rekt.left()){
            MyLabel->move(rekt.bottomLeft());
        }
        if(rekt.top() < rekt.bottom() && rekt.right() < rekt.left()){
            MyLabel->move(rekt.topRight());
        }
        if(rekt.top() < rekt.bottom() && rekt.right() > rekt.left()){
            MyLabel->move(rekt.topLeft());
        }
    }
    if(event->key()==Qt::Key_Left){
        rekt.translate(-30,0);
        if(rekt.top() > rekt.bottom() && rekt.right() < rekt.left()){
            MyLabel->move(rekt.bottomRight());
        }
        if(rekt.top() > rekt.bottom() && rekt.right() > rekt.left()){
            MyLabel->move(rekt.bottomLeft());
        }
        if(rekt.top() < rekt.bottom() && rekt.right() < rekt.left()){
            MyLabel->move(rekt.topRight());
        }
        if(rekt.top() < rekt.bottom() && rekt.right() > rekt.left()){
            MyLabel->move(rekt.topLeft());
        }
    }
    update();
}

void MyMainWindow::paintEvent(QPaintEvent*){
    QSize size=this->size();
    QPainter painter1(this);
    painter1.drawLine(0,size.height(),size.width(),25);
    painter1.setPen(Qt::DashLine);
    painter1.drawRect(rekt);
    QPainter painter2(this);
    painter2.drawRect(rekt);
}

void MyMainWindow::FileSaveAsMenu(){
    QString fileName = QFileDialog::getSaveFileName(this,"Save As...", "", "FESB File (*.fsb)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this,"Unable to Open File", file.errorString());
            return;
        }
        QTextStream out(&file);
        out << "fesb file" << Qt::endl;
        out << MyLabel->text() << Qt::endl;
        out << MyLabel->pos().x() << Qt::endl;
        out << MyLabel->pos().y() << Qt::endl;
        out << rekt.topLeft().x() << Qt::endl;
        out << rekt.topLeft().y() << Qt::endl;
        out << rekt.bottomRight().x()<< Qt::endl;
        out << rekt.bottomRight().y()<<Qt::endl;
        out << pos().x() << Qt::endl;
        out << pos().y() << Qt::endl;
        out << size().width() << Qt::endl;
        out << size().height() << Qt::endl;
    }
}

void MyMainWindow::FileOpenMenu(){
    QString fileName = QFileDialog::getOpenFileName(this,"Open Geometry...", "", "FESB File (*.fsb)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "Unable to Open File", file.errorString());
            return;
        }
        QTextStream in(&file);
        QString str;
        str = in.readLine();
        if(str=="fesb file") {
            str = in.readLine();
            MyLabel->setText(str);
            int x, y, w, h;
            in >> x >> y;
            MyLabel->move(x, y);
            int tx, ty, bx, by;
            in >> tx >> ty >> bx >> by;
            rekt.setTopLeft(QPoint(tx,ty));
            rekt.setBottomRight(QPoint(bx,by));
            in >> x >> y >> w >> h;
            this->setGeometry(x, y, w, h);
        }
    }
}

int main(int argc, char **argv) {
    QApplication app (argc, argv);
    MyMainWindow mainWindow;
    mainWindow.resize(700,500);
    mainWindow.show();
    return app.exec();
}

#!/usr/bin/env python3

from PyQt5 import QtWidgets, QtCore, QtGui
import sys, math, locale, re

class MainUI(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.result_list = []
        self.volume = 0
        self.lis_types = (None, Krug, Kvadrat, Pryamo, Cyl, Shestiug, Grani_Shest)
        self.template_list = (None, Shabl_shaiba, Shabl_paral, Shabl_cyl, Shabl_vtul)
        self.start_txt = "Общая площадь: 0 дм<sup>2</sup>"
        self.result_txt = "Общая площадь: {0:10n} дм<sup>2</sup>"
        self.mainbox = QtWidgets.QVBoxLayout()
        self.result = QtWidgets.QLabel(self.start_txt)
        self.result.setStyleSheet("font: 13pt Arial")
        self.addbtn = QtWidgets.QPushButton("Добавить")
        self.addbtn.setShortcut(QtCore.Qt.Key_Return)
        self.addbtn.clicked.connect (self.get_calculate)
        self.combo_shab()
        self.generate_options()
        self.start_buttons()
        self.start_list()
        self.buf = QtWidgets.QApplication.clipboard()
        self.mainbox.addLayout(self.shabl)
        self.mainbox.addLayout(self.qbox)
        self.mainbox.addWidget(self.option)
        self.mainbox.addWidget(self.addbtn)
        self.mainbox.addWidget(self.mainlist)
        self.mainbox.addLayout(self.qbox1)
        self.mainbox.addWidget(self.result)
        self.setLayout(self.mainbox)
        self.setWindowTitle("Расчёт площади")
    
    def start_buttons (self):
        self.qbox = QtWidgets.QGridLayout()
        j = 0
        z = 0
        btn_list = []
        for x in self.lis_types[1:]:
            a = QtWidgets.QPushButton(x.name)
            a.clicked.connect(lambda check, n=x.type: self.option.setCurrentIndex(n))
            btn_list.append(a)
        for i in btn_list:
            self.qbox.addWidget(i, j//2, z)
            z = 0 if z == 1 else 1
            j+=1
            
    def combo_shab (self):
        self.combo = QtWidgets.QComboBox()
        self.shabl = QtWidgets.QHBoxLayout()
        self.combo.addItem("Шаблон не установлен")
        items = (x.name for x in self.template_list[1:])
        self.combo.addItems(items)
        btn_shab = QtWidgets.QPushButton("Добавить шаблон")
        btn_shab.setShortcut(QtCore.Qt.Key_Return)
        self.shabl.addWidget(self.combo)
        self.shabl.addWidget(btn_shab)
        btn_shab.clicked.connect (self.add_shab)
        
    def generate_options (self):
        self.list_fig = []
        self.list_fig.append(QtWidgets.QLabel("Фигура не выбрана"))
        for i in self.lis_types[1:]:
            self.list_fig.append(i())
        self.option = QtWidgets.QStackedWidget()
        self.option.addWidget(self.list_fig[0])
        for x in self.list_fig[1:]:
            y = QtWidgets.QWidget()
            y.setLayout(x.vbox)
            self.option.addWidget(y)
            
    def start_list (self):
        btn_udal = QtWidgets.QPushButton("Удалить")
        btn_izm = QtWidgets.QPushButton("Изменить")
        btn_new = QtWidgets.QPushButton("Сбросить")
        btn_copy = QtWidgets.QPushButton("Скопировать")
        btn_udal.clicked.connect (self.udalit)
        btn_izm.clicked.connect (self.izmenit)
        btn_new.clicked.connect (self.sbrosit)
        btn_copy.clicked.connect (self.skopirivat)
        self.qbox1 = QtWidgets.QGridLayout()
        self.qbox1.addWidget(btn_udal, 0, 0)
        self.qbox1.addWidget(btn_izm, 0, 1)
        self.qbox1.addWidget(btn_new, 1, 0)
        self.qbox1.addWidget(btn_copy, 1, 1)
        self.mainlist = QtWidgets.QListView()
        self.m_list = QtGui.QStandardItemModel()
        self.mainlist.setModel (self.m_list)
        
    def get_calculate (self):
        i = self.option.currentIndex()
        try:
            if i == 0:
                return
            s = self.list_fig[i].calculate()
        except ValueError:
            return
        self.result_list.append(s)
        self.volume += s.v
        self.result.setText(self.result_txt.format(self.volume))
        self.m_list.appendRow(QtGui.QStandardItem(s.text))
        
    def add_shab(self):
        i = self.combo.currentIndex()
        if i == 0:
            return
        self.shabl_class = self.template_list[i]()
        shablbox = QtWidgets.QVBoxLayout()
        btn1 = QtWidgets.QPushButton ("Добавить")
        btn1.clicked.connect(self.close_dialog_shabl)
        shablbox.addLayout(self.shabl_class.vbox)
        shablbox.addWidget(btn1)
        self.dialog2 = QtWidgets.QWidget(self, QtCore.Qt.Window)
        self.dialog2.setWindowModality(QtCore.Qt.WindowModal)
        self.dialog2.setWindowTitle("Шаблон")
        self.dialog2.setLayout(shablbox)
        self.dialog2.show()
        
    def udalit(self):
        x = self.mainlist.currentIndex()
        x = x.row()
        if x <0:
            return
        self.m_list.removeRow(x)
        y = self.result_list.pop(x)
        self.volume -=y.v
        self.result.setText(self.result_txt.format(self.volume))
        
    def skopirivat(self):
        if self.buf:
            i = int(math.floor(math.log10(math.fabs(self.volume))))
            s = str(round(self.volume, -(i-2)))
            s = s.replace(".",",")
            self.buf.setText(s)
        
    def izmenit(self):
        x = self.mainlist.currentIndex()
        self.indx = x.row()
        if self.indx <0:
            return
        for_change = self.result_list[self.indx]
        izmbox = QtWidgets.QVBoxLayout()
        #сделать так чтобы не зависить от индексов
        btn1 = QtWidgets.QPushButton ("Изменить")
        btn1.setShortcut(QtCore.Qt.Key_Return)
        self.izmclass = self.lis_types[for_change.type]()
        self.izmclass.izmena(for_change)
        self.volume -=for_change.v
        izmbox.addLayout(self.izmclass.vbox)
        izmbox.addWidget(btn1)
        self.dialog1 = QtWidgets.QWidget(self, QtCore.Qt.Window)
        btn1.clicked.connect (self.close_dialog)
        self.dialog1.setLayout(izmbox)
        self.dialog1.setWindowTitle("Изменить")
        self.dialog1.setWindowModality(QtCore.Qt.WindowModal)
        self.dialog1.show()
        
    def sbrosit(self):
        self.result_list = []
        self.volume = 0
        self.result.setText(self.start_txt)
        self.m_list.clear()
        
    def close_dialog(self):
        self.dialog1.close()
        try:
            y = self.izmclass.calculate()
        except ValueError:
            return
        self.result_list[self.indx] = y
        self.volume +=y.v
        self.m_list.setItem(self.indx,QtGui.QStandardItem(y.text))
        self.result.setText(self.result_txt.format(self.volume))
        
    def close_dialog_shabl(self):
        try:
            y = self.shabl_class.calculate()
        except ValueError:
            return
        self.dialog2.close()
        for x in y:
            self.result_list.append(x)
            self.volume += x.v
            self.m_list.appendRow(QtGui.QStandardItem(x.text))
        self.result.setText(self.result_txt.format(self.volume))
             
        
class Krug(QtWidgets.QWidget):

    text1 = "Диаметр круга в мм:"
    text2 = "Коэфицент:"
    type = 1
    name = "Круг"
    numberPattern = re.compile("^\\d+\\.?\\d*|[+-]\\d+\\.?\\d*")
    
    def calculate(self):
        x, y = self.cifr()
        v = y*math.pi*x**2/40000
        return Result(v, "Круг V:{2:.3f} ⌀:{0:.2f}, k:{1:.2f}, ".format(x, y, v), (self.line1.text(), self.line2.text()), self.type)
        
    def getclear(self):
        self.line1.clear()
        self.line2.clear()
        
    def cifr (self):
        a = self.line1.text()
        if a =="":
            raise ValueError
        b = self.line2.text()
        a = self.parseToDigit(a)
        if b == "":
            b = 1
        else:
            b = self.parseToDigit(b)
        if a < 0:
            a = math.fabs(a)
            if b > 0:
                b = -b
        return a, b
        
    def parseToDigit(self, input):
        if "," in input:
            input = input.replace(",",".")
        if " " in input:
            input = input.replace(" ","")
        lst = self.numberPattern.findall(input)
        result = 0
        for x in lst:
            result+=float(x)
        return result

    def getUI (self):
        self.vbox = QtWidgets.QVBoxLayout()
        self.validator = QtGui.QRegExpValidator(QtCore.QRegExp("-?\d+[,.]?\d* *([+-] *\d+[,.]?\d*)*"))
        self.lab1 = QtWidgets.QLabel (self.text1)
        self.line1 = QtWidgets.QLineEdit()
        self.line1.setValidator(self.validator)
        lab2 = QtWidgets.QLabel (self.text2)
        self.line2 = QtWidgets.QLineEdit()
        self.line2.setValidator(self.validator)
        self.vbox.addWidget(self.lab1)
        self.vbox.addWidget(self.line1)
        self.extra()
        self.vbox.addWidget(lab2)
        self.vbox.addWidget(self.line2)
        
    def extra(self):
        pass
        
    def __init__(self):
        self.getUI()
        
    def izmena (self, result):
        self.line1.setText(result.mainlist[0])
        self.line2.setText(result.mainlist[1])
        
class Kvadrat (Krug):
    text1 = "Сторона квадрата в мм:"
    type = 2
    name = "Квадрат"
    
    def calculate(self):
        x, y = self.cifr()
        v = y*x**2/10000
        return Result(v, "Квадрат V:{2:.3f} а:{0:.2f}, k:{1:.2f}".format(x, y, v), (self.line1.text(), self.line2.text()), self.type)

class Pryamo (Krug):
    text1 = "Сторона а прямоугольника, мм:"
    text11 = "Сторона b прямоугольника, мм:"
    type = 3
    name = "Прямоугольник"
    
    def extra (self):
        lab11 = QtWidgets.QLabel (self.text11)
        self.line11 = QtWidgets.QLineEdit()
        self.line11.setValidator(self.validator)
        self.vbox.addWidget(lab11)
        self.vbox.addWidget(self.line11)
        
    def izmena (self, result):
        self.line1.setText(result.mainlist[0])
        self.line11.setText(result.mainlist[1])
        self.line2.setText(result.mainlist[2])
        
    def cifr (self):
        a = self.line1.text()
        a1 = self.line11.text()
        if a == "" or a1 == "":
            raise ValueError
        b = self.line2.text()
        if b == "":
            b = 1
        else:
            b = self.parseToDigit(b)
        a = self.parseToDigit(a)
        a1 = self.parseToDigit(a1)
        if a<0 or a1<0:
            a = math.fabs(a)
            a1 = math.fabs(a1)
            if b > 0:
                b = -b
        return a, a1, b
        
    def getclear(self):
        self.line1.clear()
        self.line11.clear()
        self.line2.clear()

            
    def calculate(self):
        a, b, x = self.cifr()
        v = x*a*b/10000
        str1 = "Прямоуг. V:{3:.3f} {0:.2f}×{1:.2f} k: {2:.2f}".format(a, b, x, v)
        return Result(v, str1, (self.line1.text(), self.line11.text(), self.line2.text()), self.type)

class Shestiug (Krug):
    text1 = "Диаметр вписанной окружности в мм:"
    type = 5
    name = "Шестиугольник"
    extra_txt = "Диаметр описанной окружности в мм:"
    check_box_name = "Описанная окружность"
    
    def calculate(self):
        x, y = self.cifr()
        if self.check1.checkState():
            v = y*1.5*math.sqrt(3)*x**2/40000
            return Result(v, "Шестиугольник V:{2:.3f} R:{0:.2f}, k:{1:.2f}, ".format(x, y, v), (self.line1.text(), self.line2.text(), True), self.type)
        else:
            v = y*math.sqrt(12)*x**2/40000
            return Result(v, "Шестиугольник V:{2:.3f} r:{0:.2f}, k:{1:.2f}, ".format(x, y, v), (self.line1.text(), self.line2.text(), False), self.type)
        
    def extra (self):
        self.check1 = QtWidgets.QCheckBox(self.check_box_name)
        self.check1.toggled.connect(lambda: self.on_check())
        self.vbox.addWidget(self.check1)
        
    def on_check (self):
        if self.check1.checkState() == 2:
            self.lab1.setText(self.extra_txt)
        else: 
            self.lab1.setText(self.text1)
            
    def izmena (self, result):
        self.line1.setText(result.mainlist[0])
        self.line2.setText(result.mainlist[1])
        if result.mainlist[2]:
            self.check1.setCheckState(QtCore.Qt.Checked)
        else:
            self.check1.setCheckState(QtCore.Qt.Unchecked)

class Grani_Shest (Shestiug):
    text11 = "Высота призмы, мм:"
    type = 6
    name = "Призма (N=6)"
    
    def extra (self):
        lab11 = QtWidgets.QLabel (self.text11)
        self.line11 = QtWidgets.QLineEdit()
        self.line11.setValidator(self.validator)
        self.vbox.addWidget(lab11)
        self.vbox.addWidget(self.line11)
        super().extra()
    
    def calculate(self):
        x, y, z = self.cifr()
        if self.check1.isChecked():
            v = z*y*x*6/20000
            s = "Призма-N6 V:{3:.3f} R:{0:.2f}, h:{1:.2f}, k:{2:.2f}, ".format(x, y, z, v)
            return Result(v, s, (self.line1.text(), self.line11.text(), self.line2.text(), True), self.type)
        else:
            v = z*y*math.sqrt(3)*x*6/40000
            s = "Призма-N6 V:{3:.3f} r:{0:.2f}, h:{1:.2f}, k:{2:.2f}, ".format(x, y, z, v)
            return Result(v, s, (self.line1.text(), self.line11.text(), self.line2.text(), False), self.type)
    
    def cifr(self):
        return Pryamo.cifr(self)
        
    def izmena(self, result):
        Pryamo.izmena(self, result)
        if result.mainlist[3]:
            self.check1.setCheckState(QtCore.Qt.Checked)
        else:
            self.check1.setCheckState(QtCore.Qt.Unchecked)
            
class Cyl (Grani_Shest):
    text1 = "Диаметр цилиндра, мм:"
    text11 = "Высота цилиндра, мм:"
    type = 4
    name = "Цилиндр"
    extra_txt = "Цилиндр с резьбой, мм:"
    check_box_name = "Резьба"
   
    def calculate(self):
        a, b, x = self.cifr()
        v = x*math.pi*a*b/10000
        if self.check1.isChecked():
            v *= 1.5
            str1 = "Резьба V:{3:.3f} М:{0:.2f} h:{1:.2f} k:{2:.2f}".format(a, b, x, v)
        else:
            str1 = "Цилиндр V:{3:.3f} ⌀:{0:.2f} h:{1:.2f} k:{2:.2f}".format(a, b, x, v)
        return Result(v, str1, (self.line1.text(), self.line11.text(), self.line2.text(), False), self.type) 
            
class Shabl_shaiba(Krug):
    text1 = "Диаметр шайбы, мм"
    text2 = "Диаметр отверстия, мм"
    name = "Шайба с отверстием"
    
    def cifr (self):
        a = self.line1.text()
        b = self.line2.text()
        if "," in a:
            a = a.replace(",",".")
        if "," in b:
            b = b.replace(",",".")
        a = float(a)
        b = float(b)
        if a < 0:
            a = math.fabs(a)
        if b < 0:
            b = math.fabs(b)
        return a, b
    
    def calculate(self):
        x, y = self.cifr()
        v1 = 2*math.pi*x**2/40000
        v2 = -2*math.pi*y**2/40000
        res1 = Result(v1, "Круг V:{2:.3f} ⌀:{0:.2f}, k:{1:.2f}, ".format(x, 2, v1),
        (self.line1.text(), "2"), 1)
        res2 = Result(v2, "Круг V:{2:.3f} ⌀:{0:.2f}, k:{1:.2f}, ".format(y, -2, v2),
        (self.line1.text(), "-2"), 1)
        return res1, res2
 
class Shabl_paral (Pryamo):
    text1 = "Сторона а, мм:"
    text11 = "Сторона b, мм:"
    text2 = "Сторона c, мм:"
    name = "Параллелепипед"
    
    def calculate(self):
        x, y, z = self.cifr()
        v1 = x*y/5000
        v2 = x*z/5000
        v3 = 2*z*y/10000
        res1 = Result(v1, "Прямоуг. V:{3:.3f} а:{0:.2f} b:{1:.2f} k: {2:.2f}".format(x, y, 2, v1), (self.line1.text(), self.line11.text(), "2"), 3)
        res2 = Result(v2, "Прямоуг. V:{3:.3f} а:{0:.2f} b:{1:.2f} k: {2:.2f}".format(x, z, 2, v2), (self.line1.text(), self.line2.text(), "2"), 3)
        res3 = Result(v3, "Прямоуг. V:{3:.3f} а:{0:.2f} b:{1:.2f} k: {2:.2f}".format(z, y, 2, v3), (self.line2.text(), self.line11.text(), "2"), 3)
        return res1, res2, res3   
        
    def cifr (self):
        a = self.line1.text()
        b = self.line11.text()
        c = self.line2.text()
        i=[]
        for x in a, b, c:
            if "," in x:
                x = x.replace(",",".")
            x = float(x)
            if x < 0:
                x = math.fabs(x)
            i.append(x)   
        return i
        
class Shabl_cyl(Shabl_shaiba):
    name = "Полный цилиндр"
    text1 = "Диаметр цилиндра, мм:"
    text2 = "Высота цилиндра, мм:"
    
    def calculate(self):
        x, y = self.cifr()
        v1 = 2*math.pi*x**2/40000
        v2 = math.pi*x*y/10000
        s1 = "Цилиндр V:{3:.3f} ⌀:{0:.2f} h:{1:.2f} k:{2:.2f}".format(x, y, 1, v1)
        s2 = "Круг V:{2:.3f} ⌀:{0:.2f}, k:{1:.2f}, ".format(x, 2, v2)
        res1 = Result(v1, s2, (self.line1.text(), "2"), 1)
        res2 = Result(v2, s1, (self.line1.text(), self.line2.text(), "1", False), 4)
        return res1, res2
        
class Shabl_vtul(Pryamo):
    name = "Втулка"
    text1 = "Диаметр втулки, мм:"
    text11 = "Высота втулки, мм:"
    text2 =  "Диаметр отверстия, мм"
    
    def cifr (self):
        return (math.fabs(self.parseToDigit(i)) for i in
        (self.line1.text(), self.line2.text(), self.line11.text()))
        
    def calculate(self):
        d1, d2, h = self.cifr()
        v1 = 2*math.pi*d1**2/40000
        s1 = "Круг V:{2:.3f} ⌀:{0:.2f}, k:{1:.2f}, ".format(d1, 2, v1)
        res1 = Result(v1, s1, (self.line1.text(), "2"), 1)
        v2 = -2*math.pi*d2**2/40000
        s2 = "Круг V:{2:.3f} ⌀:{0:.2f}, k:{1:.2f}, ".format(d2, -2, v2)
        res2 = Result(v2, s2, (self.line2.text(), "-2"), 1)
        v3 = math.pi*d1*h/10000
        s3 = "Цилиндр V:{3:.3f} ⌀:{0:.2f} h:{1:.2f} k:{2:.2f}".format(d1, h, 1, v3)
        res3 = Result(v3, s3, (self.line1.text(), self.line11.text(), "1", False), 4)
        v4 = math.pi*d2*h/10000
        s4 = "Цилиндр V:{3:.3f} ⌀:{0:.2f} h:{1:.2f} k:{2:.2f}".format(d2, h, 1, v4)
        res4 = Result(v4, s4, (self.line2.text(), self.line11.text(), "1", False), 4)
        return res1, res2, res3, res4
        
                
class Result ():
    def __init__(self, obyom, txt, data_list, type):
        self.v = obyom
        self.text = txt
        self.mainlist = data_list
        self.type = type
        
         
if __name__ == "__main__":
    #locale.setlocale (locale.LC_ALL, "ru")
    app = QtWidgets.QApplication(sys.argv)
    M = MainUI()
    M.show()
    sys.exit(app.exec())

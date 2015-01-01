/*
Name: QtRpt
Version: 1.4.4
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#include "qtrpt.h"

#include <QApplication>
#include <QAction>
#include <QTime>
#include <QFile>
#include <QPrintPreviewDialog>
#include <QDesktopWidget>
#include <QPrinterInfo>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextBlock>

/*!
 * \class QtRPT
 * \brief The QtRPT class is the base class of the QtRPT
 * \param parent
*/

QtRPT::QtRPT(QWidget *parent) : QWidget(parent) {
    xmlDoc = new QDomDocument("Reports");
    m_backgroundImage = 0;
    m_orientation = 0;
    rptSql = 0;
}

bool QtRPT::loadReport(QString fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    else {
        listOfPair.clear();
        listIdxOfGroup.clear();
    }
    if (!xmlDoc->setContent(&file)) {
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool QtRPT::loadReport(QDomDocument xmlDoc) {
    QtRPT::xmlDoc = &xmlDoc;
    return true;
}

QDomNode QtRPT::getBand(BandType type, QDomElement docElem) {
    QString s_type;
    if (type == ReportTitle)     s_type = "ReportTitle";
    if (type == PageHeader)      s_type = "PageHeader";
    if (type == MasterData)      s_type = "MasterData";
    if (type == PageFooter)      s_type = "PageFooter";
    if (type == ReportSummary)   s_type = "ReportSummary";
    if (type == MasterFooter)    s_type = "MasterFooter";
    if (type == MasterHeader)    s_type = "MasterHeader";
    if (type == DataGroupHeader) s_type = "DataGroupHeader";
    if (type == DataGroupFooter) s_type = "DataGroupFooter";
    //QDomElement docElem = xmlDoc->documentElement();  //get root element
    QDomNode n = docElem.firstChild();//.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if ((!e.isNull()) && (e.tagName() == "ReportBand")) {
            if (e.attribute("type") == s_type) {
                return n;
            }
        }
        n = n.nextSibling();
    }
    return n;
}

void QtRPT::setFont(QDomElement e) {
    QFont font(e.attribute("fontFamily"),e.attribute("fontSize").toInt());
    font.setBold(processHighligthing(e, FntBold).toInt());
    font.setItalic(processHighligthing(e, FntItalic).toInt());
    font.setUnderline(processHighligthing(e, FntUnderline).toInt());
    font.setStrikeOut(processHighligthing(e, FntStrikeout).toInt());

    painter.setFont(font);
    painter.setPen(Qt::black);
}

Qt::Alignment QtRPT::getAligment(QDomElement e) {
    Qt::Alignment al;
    Qt::Alignment alH, alV;
    if (e.attribute("aligmentH") == "hRight")   alH = Qt::AlignRight;
    if (e.attribute("aligmentH") == "hLeft")    alH = Qt::AlignLeft;
    if (e.attribute("aligmentH") == "hCenter")  alH = Qt::AlignHCenter;
    if (e.attribute("aligmentH") == "hJustify") alH = Qt::AlignJustify;
    if (e.attribute("aligmentV") == "vTop")     alV = Qt::AlignTop;
    if (e.attribute("aligmentV") == "vBottom")  alV = Qt::AlignBottom;
    if (e.attribute("aligmentV") == "vCenter")  alV = Qt::AlignVCenter;
    return al = alH | alV;
}

QPen QtRPT::getPen(QDomElement e) {
    QPen pen = painter.pen();
    //Set border width
    pen.setWidth(e.attribute("borderWidth","1").replace("px","").toInt()*5);
    //Set border style
    QString borderStyle = e.attribute("borderStyle","solid");
    pen.setStyle(getPenStyle(borderStyle));
    return pen;
}

Qt::PenStyle QtRPT::getPenStyle(QString value) {
    Qt::PenStyle style;
    if (value == "dashed") style = Qt::DashLine;
    else if (value == "dotted") style = Qt::DotLine;
    else if (value == "dot-dash") style = Qt::DashDotLine;
    else if (value == "dot-dot-dash") style = Qt::DashDotDotLine;
    else style = Qt::SolidLine;
    return style;
}

FieldType QtRPT::getFieldType(QDomElement e) {
    if (e.attribute("type","label") == "barcode") {
        return Barcode;
    } else if (e.attribute("type","label") == "reactangle") {
        return Reactangle;
    } else if (e.attribute("type","label") == "roundedReactangle") {
        return RoundedReactangle;
    } else if (e.attribute("type","label") == "circle") {
        return Circle;
    } else if (e.attribute("type","label") == "triangle") {
        return Triangle;
    } else if (e.attribute("type","label") == "rhombus") {
        return Rhombus;
    } else if (e.attribute("type","label") == "textRich") {
        return TextRich;
    } else if (e.attribute("type","label") == "label") {
        return Text;
    } else if (e.attribute("type","label") == "labelImage") {
        return TextImage;
    } else if (e.attribute("type","label") == "image" || e.attribute("picture","text") != "text") {
        return Image;
    } else if (e.attribute("type","label") == "diagram") {
        return Diagram;
    } else if (e.attribute("type","label") == "line") {
        return Line;
    } else return Text;
}

QString QtRPT::getFieldTypeName(FieldType type) {
    switch (type) {
        case Reactangle: return "reactangle";
        case RoundedReactangle: return "roundedReactangle";
        case Circle: return "circle";
        case Triangle: return "triangle";
        case Rhombus: return "rhombus";
        case TextRich: return "textRich";
        case Text: return "label";
        case TextImage: return "labelImage";
        case Image: return "image";
        case Diagram: return "diagram";
        case Line: return "line";
        case Barcode: return "barcode";
        default: return "label";
    }
}

QList<FieldType> QtRPT::getDrawingFields() {
    QList<FieldType> set;
    set<<Circle<<Triangle<<Rhombus<<RoundedReactangle<<Reactangle;
    return set;
}

void QtRPT::drawFields(QDomNode band, QDomElement e, int bandTop, bool draw) {
    int left_ = e.attribute("left").toInt()*koefRes_w;    
    int width_ = (e.attribute("width").toInt()-1)*koefRes_w;
    int height_ = e.attribute("height").toInt()*koefRes_h;
    int top_ = (bandTop+e.attribute("top").toInt())*koefRes_h;
    if (e.attribute("autoHeight","0").toInt() == 1) {        
        height_ = band.toElement().attribute("realHeight").toInt()*koefRes_h;
    }    

    FieldType fieldType = getFieldType(e);
    QPen pen = getPen(e);

    if (draw) {        
        //return;
        if (!getDrawingFields().contains(fieldType) && fieldType != Barcode) {
            //Fill background
            if ( colorFromString(processHighligthing(e, BgColor).toString() )  != QColor(255,255,255,0)) {
                painter.fillRect(left_+1,top_+1,width_-2,height_-2,colorFromString(processHighligthing(e, BgColor).toString()));
            }
            //Draw frame
            if ( colorFromString(e.attribute("borderTop")) != QColor(255,255,255,0) ) {
                pen.setColor(colorFromString(e.attribute("borderTop")));
                painter.setPen(pen);
                painter.drawLine(left_, top_, left_ + width_, top_);
            }
            if ( colorFromString(e.attribute("borderBottom")) != QColor(255,255,255,0) ) {
                pen.setColor(colorFromString(e.attribute("borderBottom")));
                painter.setPen(pen);
                painter.drawLine(left_, top_ + height_, left_ + width_, top_ + height_);
            }
            if ( colorFromString(e.attribute("borderLeft")) != QColor(255,255,255,0) ) {
                pen.setColor(colorFromString(e.attribute("borderLeft")));
                painter.setPen(pen);
                painter.drawLine(left_, top_, left_, top_ + height_);
            }
            if ( colorFromString(e.attribute("borderRight")) != QColor(255,255,255,0) ) {
                pen.setColor(colorFromString(e.attribute("borderRight")));
                painter.setPen(pen);
                painter.drawLine(left_ + width_, top_, left_ + width_, top_ + height_);
            }
        }
        if (fieldType == Rhombus) {
            qreal pointX1 = width_/2+left_;
            qreal pointY1 = height_-1+top_;

            qreal pointX2 = width_ + left_;
            qreal pointY2 = height_/2+top_;

            qreal pointX3 = width_/2+left_;
            qreal pointY3 = top_+1;  //

            qreal pointX4 = left_+1;  //
            qreal pointY4 = height_/2+top_;

            QPainterPath path;
            path.moveTo (pointX1, pointY1);
            path.lineTo (pointX2, pointY2);
            path.lineTo (pointX3, pointY3);
            path.lineTo (pointX4, pointY4);
            path.lineTo (pointX1, pointY1);

            QBrush brush(colorFromString(processHighligthing(e, BgColor).toString()));
            pen.setColor(colorFromString(e.attribute("borderColor")));
            painter.drawPath(path);
            painter.fillPath (path, brush);
        }
        if (fieldType == Triangle) {
            qreal pointX1 = left_;
            qreal pointY1 = height_-1+top_;

            qreal pointX2 = width_+left_;
            qreal pointY2 = height_-1+top_;

            qreal pointX3 = width_/2+left_;
            qreal pointY3 = top_;

            QPainterPath path;
            path.moveTo (pointX1, pointY1);
            path.lineTo (pointX2, pointY2);
            path.lineTo (pointX3, pointY3);
            path.lineTo (pointX1, pointY1);

            QBrush brush(colorFromString(processHighligthing(e, BgColor).toString()));
            pen.setColor(colorFromString(e.attribute("borderColor")));
            painter.drawPath(path);
            painter.fillPath (path, brush);
        }
        if (fieldType == RoundedReactangle) {
            QRectF rect(left_,top_,width_-2,height_-2);
            QBrush brush(colorFromString(processHighligthing(e, BgColor).toString()));
            pen.setColor(colorFromString(e.attribute("borderColor")));
            painter.setBrush(brush);
            painter.drawRoundedRect(rect, 4, 4);
        }
        if (fieldType == Reactangle) {
            QRectF rect(left_,top_,width_-2,height_-2);
            QBrush brush(colorFromString(processHighligthing(e, BgColor).toString()));
            pen.setColor(colorFromString(e.attribute("borderColor")));
            painter.setBrush(brush);
            painter.drawRect(rect);
        }
        if (fieldType == Circle) {
            QBrush brush(colorFromString(processHighligthing(e, BgColor).toString()));
            painter.setBrush(brush);
            pen.setColor(colorFromString(e.attribute("borderColor")));
            painter.setPen(pen);
            painter.drawEllipse(left_, top_, width_, height_);
        }
        /*if (fieldType == TextImage) { //Proccess field as ImageField
            QImage image = sectionFieldImage(e.attribute("value"));
            if (!image.isNull()) {
                QRectF target(left_, top_, width_, height_);
                painter.drawImage(target,image);
            }
        }*/
        if (fieldType == TextImage) { //Proccess field as ImageField
            QImage image = sectionFieldImage(e.attribute("value"));
            if (!image.isNull()) {
                QImage scaledImage = image.scaled(QSize(width_,height_),Qt::KeepAspectRatio);
                QPoint point(left_, top_);
                Qt::Alignment alignment = this->getAligment(e);
                // Horizontal Center
                if (alignment.testFlag(Qt::AlignHCenter)) {
                    int offsetX = (width_ - scaledImage.width()) / 2;
                    point.setX(left_ + offsetX);
                }
                // Vertical Center
                if (alignment.testFlag(Qt::AlignVCenter)) {
                    int offsetY = (height_ - scaledImage.height()) / 2;
                    point.setY(top_ + offsetY);
                }
                painter.drawImage(point,scaledImage);
            }
        }
        if (fieldType == Image) {  //Proccess as static ImageField
            QString m_imgFormat = e.attribute("imgFormat","PNG");
            QByteArray byteArray;
            byteArray = QByteArray::fromBase64(e.attribute("picture","text").toLatin1());
            QPixmap pixmap = QPixmap::fromImage(QImage::fromData(byteArray, m_imgFormat.toLatin1().data()));

            if (e.attribute("ignoreAspectRatio","1").toInt() == 1) {
                painter.drawPixmap(left_,top_,width_,height_,pixmap);
            } else {
                painter.drawPixmap(left_,top_,pixmap.width()*koefRes_w,pixmap.height()*koefRes_h,pixmap);
            }
        }
        if (fieldType == Diagram) {
            Chart *chart = new Chart();
            chart->setObjectName(e.attribute("name"));
            chart->setParams(e.attribute("showGrid","1").toInt(),
                             e.attribute("showLegend","1").toInt(),
                             e.attribute("showCaption","1").toInt(),
                             e.attribute("showGraphCaption","1").toInt(),
                             e.attribute("showPercent","1").toInt(),
                             e.attribute("caption","Example"),
                             e.attribute("autoFillData","0").toInt()
                             );
            chart->clearData();
            chart->setKoef(koefRes_w, koefRes_h, left_, top_);
            chart->resize(width_,height_);
            //chart->setVisible(true);
            if (e.attribute("autoFillData","0") == "0") {
                emit setValueDiagram(*chart);
            } else {
                QDomNode g = e.firstChild();
                while(!g.isNull()) {
                    QDomElement ge = g.toElement(); // try to convert the node to an element.

                    GraphParam param;
                    param.color = colorFromString( ge.attribute("color") );
                    param.valueReal = sectionField(g, ge.attribute("value"), false).toFloat();
                    param.caption = ge.attribute("caption");
                    chart->setData(param);

                    g = g.nextSibling();
                }
            }
            chart->paintChart(&painter);
        }
        if (fieldType == Barcode) {
            BarCode *br = new BarCode(this);
            br->setObjectName(e.attribute("name"));
            QString txt = sectionField(band, e.attribute("value"), false, false, "");
            br->setValue(txt);
            BarCode::BarcodeTypes m_barcodeType = (BarCode::BarcodeTypes)e.attribute("barcodeType","13").toInt();
            br->setBarcodeType(m_barcodeType);
            BarCode::FrameTypes m_barcodeFrameType = (BarCode::FrameTypes)e.attribute("barcodeFrameType","0").toInt();
            br->setFrameType(m_barcodeFrameType);
            br->drawBarcode(&painter,left_,top_,width_,height_);
        }
    }
    if (fieldType == TextRich) {
        QString txt = e.attribute("value");

        QTextDocument document;
        document.setHtml(txt);
        document.setDefaultFont(painter.font());

        QTextBlock block = document.firstBlock();
        while (block.isValid()) {
            for (QTextBlock::iterator it = block.begin(); !it.atEnd(); ++it) {
                QTextFragment currentFragment = it.fragment();
                if (!currentFragment.isValid())
                    continue;

                if ((currentFragment.text().contains("[") && currentFragment.text().contains("]")) ||
                    (currentFragment.text().contains("<") && currentFragment.text().contains(">")))
                {
                    QString tmpTxt = sectionField(band, currentFragment.text(), false, false, "");
                    QTextCursor c = document.find(currentFragment.text(),QTextDocument::FindWholeWords);
                    if (tmpTxt.isEmpty() || tmpTxt.isNull())
                        tmpTxt = " ";
                    c.insertText(tmpTxt);
                }
            }
            block = block.next();
        }

        QRectF rect = QRectF(left_+10, top_, width_-15, height_);
        document.setTextWidth( rect.width() );
        painter.save();
        painter.translate( rect.topLeft() );
        document.drawContents( &painter, rect.translated( -rect.topLeft() ) );
        painter.restore();
    }
    if (fieldType == Text) { //NOT Proccess if field set as ImageField
        setFont(e);
        QString formatString = e.attribute("format","");
        QString txt = sectionField(band, e.attribute("value"), false, false, formatString);

        pen.setColor(colorFromString(processHighligthing(e, FntColor).toString()));
        painter.setPen(pen);        
        if (draw) {
            painter.drawText(left_+10,top_,width_-15,height_, getAligment(e) | Qt::TextDontClip | Qt::TextWordWrap, txt);
        } else {
            QRect boundRect = painter.boundingRect(left_+10,top_,width_-15,height_, getAligment(e) | Qt::TextDontClip | Qt::TextWordWrap, txt);
            if (boundRect.height() > height_ && e.attribute("autoHeight","0").toInt() == 1) {
                /*To correct adjust and display a height of the band we use a param 'realHeight'.
                 Currently this param used only to correct a MasterBand. If will be needed, possible
                 correct also another bands.
                */
                band.toElement().setAttribute("realHeight", QString::number(qRound(boundRect.height()/koefRes_h)));
            }
        }
    }
}

void QtRPT::drawLines(QDomElement e, int bandTop) {
    int startX = e.attribute("lineStartX").toInt()*koefRes_w;
    int endX = e.attribute("lineEndX").toInt()*koefRes_w;

    int startY = (bandTop+e.attribute("lineStartY").toInt())*koefRes_h;
    int endY = (bandTop+e.attribute("lineEndY").toInt())*koefRes_h;

    FieldType fieldType = getFieldType(e);
    QPen pen = getPen(e);
    pen.setColor(colorFromString(e.attribute("borderColor")));
    painter.setPen(pen);
    if (fieldType == Line) {
        painter.drawLine(startX, startY, endX, endY);
    }

    QLineF line(startX,startY,endX,endY);

    //Draw arrows
    static const double Pi = 3.14159265358979323846264338327950288419717;
    static double TwoPi = 2.0 * Pi;
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
         angle = TwoPi - angle;

     QPointF sourcePoint = line.p1();
     QPointF destPoint = line.p2();
     int arrowSize= 10*koefRes_w;

     painter.setBrush(colorFromString(e.attribute("borderColor")));

     if (e.attribute("arrowStart","0").toInt() == 1) {
         QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + Pi / 3) * arrowSize,
                                                       cos(angle + Pi / 3) * arrowSize);
         QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                                       cos(angle + Pi - Pi / 3) * arrowSize);
         painter.drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
     }
     if (e.attribute("arrowEnd","0").toInt() == 1) {
         QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                                   cos(angle - Pi / 3) * arrowSize);
         QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                                   cos(angle - Pi + Pi / 3) * arrowSize);
         painter.drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
     }
}

void QtRPT::drawBandRow(QDomNode n, int bandTop, bool allowDraw) {
    n.toElement().setAttribute("realHeight", n.toElement().attribute("height").toInt() ); //set a 'realHeight' to default value
    /*First pass used to determine a max height of the band*/
    QDomNode c = n.firstChild();
    while(!c.isNull()) {
        QDomElement e = c.toElement(); // try to convert the node to an element.
        if (!e.isNull() && e.tagName() == "TContainerField" && isFieldVisible(e)) {
            drawFields(n,e,bandTop,false);
        }
        c = c.nextSibling();
    }
    /*Second pass used for drawing*/
    if (allowDraw) {
        c = n.firstChild();
        while(!c.isNull()) {
            QDomElement e = c.toElement(); // try to convert the node to an element.
            if (!e.isNull() && e.tagName() == "TContainerField" && isFieldVisible(e)) {
                drawFields(n,e,bandTop,true);
            }
            if (!e.isNull() && e.tagName() == "TContainerLine" && isFieldVisible(e)) {
                drawLines(e,bandTop);
            }
            c = c.nextSibling();
        }
    }
}

QVariant QtRPT::processHighligthing(QDomElement e, HiType type) {
    QString tmpStr = e.attribute("highlighting","");
    if (tmpStr.isEmpty() || tmpStr.isNull()) {
        switch (type) {
            case FntBold: {
                return e.attribute("fontBold").toInt();
                break;
            }
            case FntItalic: {
                return e.attribute("fontItalic").toInt();
                break;
            }
            case FntUnderline: {
                return e.attribute("fontUnderline").toInt();
                break;
            }
            case FntStrikeout: {
                return e.attribute("fontStrikeout").toInt();
                break;
            }
            case FntColor: {
                return e.attribute("fontColor");
                break;
            }
            case BgColor: {
                return e.attribute("backgroundColor");
                break;
            }
        }
    } else {
        QStringList list = tmpStr.split(";");
        const QString cond = list.at(0);
        for (int i = 1; i < list.size(); i++) {
            if (list.at(i).isEmpty()) continue;
            QString exp = list.at(i);
            if (list.at(i).contains("bold") && type == FntBold) {
                exp.remove("bold=");
                QString formulaStr = exp.insert(0,cond);
                formulaStr = sectionField(e.parentNode(),formulaStr,true);
                QScriptEngine myEngine;
                return myEngine.evaluate(formulaStr).toInteger();
            }
            if (list.at(i).contains("italic") && type == FntItalic) {
                exp.remove("italic=");
                QString formulaStr = exp.insert(0,cond);
                formulaStr = sectionField(e.parentNode(),formulaStr,true);
                QScriptEngine myEngine;
                return myEngine.evaluate(formulaStr).toInteger();
            }
            if (list.at(i).contains("underline") && type == FntUnderline) {
                exp.remove("underline=");
                QString formulaStr = exp.insert(0,cond);
                formulaStr = sectionField(e.parentNode(),formulaStr,true);
                QScriptEngine myEngine;
                return myEngine.evaluate(formulaStr).toInteger();
            }
            if (list.at(i).contains("strikeout") && type == FntStrikeout) {
                exp.remove("strikeout=");
                QString formulaStr = exp.insert(0,cond);
                formulaStr = sectionField(e.parentNode(),formulaStr,true);
                QScriptEngine myEngine;
                return myEngine.evaluate(formulaStr).toInteger();
            }
            if (list.at(i).contains("fontColor") && type == FntColor) {
                exp.remove("fontColor=");
                QString formulaStr = exp.insert(1,"'");
                formulaStr = exp.insert(0,cond);
                formulaStr = sectionField(e.parentNode(),formulaStr,true)+"':'"+e.attribute("fontColor")+"'";
                QScriptEngine myEngine;
                return myEngine.evaluate(formulaStr).toString();
            }
            if (list.at(i).contains("backgroundColor") && type == BgColor) {
                exp.remove("backgroundColor=");
                QString formulaStr = exp.insert(1,"'");
                formulaStr = exp.insert(0,cond);
                formulaStr = sectionField(e.parentNode(),formulaStr,true)+"':'"+e.attribute("backgroundColor")+"'";
                QScriptEngine myEngine;
                return myEngine.evaluate(formulaStr).toString();
            }
        }
    }
    return QVariant();
}

bool QtRPT::isFieldVisible(const QDomElement &e) {
    bool visible;
    QString formulaStr = e.attribute("printing","1");    
    if (formulaStr.size() > 1) {
        //qDebug()<<formulaStr;        
        formulaStr = sectionField(e.parentNode(),formulaStr,true);
        //qDebug()<<formulaStr;

        QScriptEngine myEngine;
        //myEngine.globalObject().setProperty("quant1","3");
        //qDebug()<<myEngine.evaluate("quant1;").toString();
        visible = myEngine.evaluate(formulaStr).toInteger();


        //QScriptValue fun = myEngine.evaluate("(function(a, b) { return a == b; })");
        //QScriptValue fun = myEngine.evaluate("if (1>2) true else false");
        //QScriptValueList args;
        /*args << "k" << "k";
        QScriptValue threeAgain = fun.call(QScriptValue(), args);
        qDebug()<<threeAgain.toString();*/

    } else {
        visible = formulaStr.toInt();
    }
    return visible;
}

QScriptValue funcAggregate(QScriptContext *context, QScriptEngine *engine) {
    Q_UNUSED(engine);

    QScriptValue self = context->thisObject();
    int funcMode = context->argument(0).toInteger();
    QString paramName = context->argument(1).toString();
    double total = 0;
    int count = 0;
    for (int i=0; i<listOfPair.size(); i++) {
        if (listOfPair.at(i).paramName == paramName) {
            if (listIdxOfGroup.size() > 0 && self.property("showInGroup").toBool() == true) {
                for (int k = 0; k < listIdxOfGroup.size(); k++) {
                    if (listIdxOfGroup.at(k) == listOfPair.at(i).lnNo) {
                        total += listOfPair.at(i).paramValue.toDouble();
                        count += 1;
                    }
                }
            } else {
                if (!listOfPair.at(i).paramValue.toString().isEmpty()) {
                    total += listOfPair.at(i).paramValue.toDouble();
                    count += 1;
                }
            }
        }
    }

    switch (funcMode) {
    case 0:  //SUM
        return total;
        break;
    case 1:  //AVG
        if (count > 0)
            return total/count;
        else
            return 0;
        break;
    case 2:  //COUNT
        return count;
        break;
    default: return 0;
    }
    return 0;
}

QStringList QtRPT::splitValue(QString value) {
    QString tmpStr;
    QStringList res;
    for (int i = 0; i < value.size(); ++i) {
        if (value.at(i) != '[' && value.at(i) != ']')
            tmpStr += value.at(i);
        else {
            if (value.at(i) == ']') {
                tmpStr += value.at(i);
                res << tmpStr;
                tmpStr.clear();
            }
            if (value.at(i) == '[') {
                if (!tmpStr.isEmpty())
                    res << tmpStr;
                tmpStr.clear();
                tmpStr += value.at(i);
            }
        }
    }
    if (!tmpStr.isEmpty()) res << tmpStr;
    return res;
}

QString QtRPT::sectionField(QDomNode bandNode, QString value, bool exp, bool firstPass, QString formatString) {
    QString tmpStr;
    QStringList res;
    bool aggregate = false;

    for (int i = 0; i < value.size(); ++i) {
        if (value.at(i) != '[' && value.at(i) != ']' &&
            value.at(i) != '<' && value.at(i) != '>' && !aggregate)
            tmpStr += value.at(i);
        else if ((value.at(i) == '[' || value.at(i) == ']') && aggregate)
             tmpStr += value.at(i);
        else if (value.at(i) != '<' && value.at(i) != '>' && aggregate)
             tmpStr += value.at(i);
        else {
            if (exp && (value.at(i) == '<' || value.at(i) == '>') )
                tmpStr += value.at(i);
            if (value.at(i) == ']' && !aggregate) {
                tmpStr += value.at(i);
                res << tmpStr;
                tmpStr.clear();
            }
            if (value.at(i) == '[' && !aggregate) {
                if (!tmpStr.isEmpty())
                    res << tmpStr;
                tmpStr.clear();
                tmpStr += value.at(i);
            }
            if (!exp && value.at(i) == '<') {
                aggregate = true;
                if (!tmpStr.isEmpty())
                    res << tmpStr;
                tmpStr.clear();
                tmpStr += value.at(i);
            }
            if (!exp && value.at(i) == '>') {
                aggregate = false;
                tmpStr += value.at(i);
                res << tmpStr;
                tmpStr.clear();
            }
        }
    }
    if (!tmpStr.isEmpty()) res << tmpStr;    

    tmpStr.clear();
    for (int i = 0; i < res.size(); ++i) {
        if (res.at(i).contains("[") && res.at(i).contains("]") && !res.at(i).contains("<") ) {
            QString tmp;
            if (rptSql != 0 ) {//if we have Sql DataSource
                if (res.at(i).contains(rptSql->objectName())) {
                    QString fieldName = res.at(i);
                    fieldName.replace("[","");
                    fieldName.replace("]","");
                    fieldName.replace(rptSql->objectName()+".","");
                    tmp = rptSql->getFieldValue(fieldName, m_recNo);
                }
            } else
                tmp = sectionValue(res.at(i));
            bool ok;
            if (exp) { //Process highlighting and visibility
                tmp.toDouble(&ok);
                if (!ok) tmp.toFloat(&ok);
                if (!ok) tmp.toInt(&ok);
                if (!ok) tmpStr += "'"+tmp+"'";  //Not a number
                else tmpStr += tmp;
            } else { //Process usuall field
                if (firstPass) { //Process during first pass to calculate aggregate values
                    AggregateValues av;
                    av.paramName = res.at(i);
                    av.paramValue = tmp;
                    av.lnNo = m_recNo;
                    av.pageReport = m_pageReport;
                    bool founded = false;
                    for (int j = 0; j < listOfPair.size(); ++j) {
                        if (listOfPair.at(j).pageReport == av.pageReport && listOfPair.at(j).lnNo == av.lnNo && listOfPair.at(j).paramName == av.paramName)
                            founded = true;
                    }
                    if (!founded)
                        listOfPair.append(av);
                }
                tmpStr += getFormattedValue(tmp, formatString); //tmp;
            }
        } else {
            if (res[i].contains("<Date>"))
                res[i] = res[i].replace("<Date>",processFunctions("Date").toString());
            if (res[i].contains("<Time>"))
                res[i] = res[i].replace("<Time>",QTime::currentTime().toString());
            if (res[i].contains("<Page>"))
                res[i] = res[i].replace("<Page>",QString::number(curPage));
            if (res[i].contains("<TotalPages>"))
                res[i] = res[i].replace("<TotalPages>",QString::number(totalPage));
            if (res[i].contains("<LineNo>"))
                res[i] = res[i].replace("<LineNo>",processFunctions("LineNo").toString());

            if (res[i].contains("<") && res[i].contains(">")) {
                QString formulaStr=res[i];
                QScriptEngine myEngine;

                QStringList tl = splitValue(formulaStr);
                for (int j = 1; j < tl.size(); ++j) {
                    if (tl.at(j).contains("[") &&
                        tl.at(j).contains("]") &&
                        !tl.at(j-1).toUpper().contains("SUM") &&
                        !tl.at(j-1).toUpper().contains("AVG") &&
                        !tl.at(j-1).toUpper().contains("COUNT")
                    )
                        formulaStr.replace(tl.at(j), sectionValue(tl.at(j)));
                }

                myEngine.globalObject().setProperty("showInGroup", bandNode.toElement().attribute("showInGroup","0").toInt());
                QScriptValue fun = myEngine.newFunction(funcAggregate);
                myEngine.globalObject().setProperty("Sum", fun);

                formulaStr = formulaStr.replace("Sum(","Sum(0,", Qt::CaseInsensitive);
                formulaStr = formulaStr.replace("Avg(","Sum(1,", Qt::CaseInsensitive);
                formulaStr = formulaStr.replace("Count(","Sum(2,", Qt::CaseInsensitive);
                formulaStr = formulaStr.replace("[","'[");
                formulaStr = formulaStr.replace("]","]'");
                formulaStr = formulaStr.replace("<","");
                formulaStr = formulaStr.replace(">","");

                QScriptValue result  = myEngine.evaluate(formulaStr);
                res[i] = getFormattedValue(result.toString(), formatString);
            }

            tmpStr += res.at(i);
        }
    }

    return tmpStr;
}

QString QtRPT::getFormattedValue(QString value, QString formatString) {
    if (!formatString.isEmpty()) {
        if (formatString.at(0) == 'N') {  //Numeric format
            int precision = formatString.mid(formatString.size()-1,1).toInt();
            QLocale locale;

            if ( formatString.mid(1,formatString.size()-2) == "# ###.##") {
                locale = QLocale(QLocale::C);
                value = locale.toString(value.toDouble(), 'f', precision).replace(","," ");
            }

            if ( formatString.mid(1,formatString.size()-2) == "#,###.##") {
                locale = QLocale(QLocale::C);
                value = locale.toString(value.toDouble(), 'f', precision);
            }

            if ( formatString.mid(1,formatString.size()-2) == "# ###,##") {
                locale = QLocale("fr_FR");
                value = locale.toString(value.toDouble(), 'f', precision);
            }
            if ( formatString.mid(1,formatString.size()-2) == "#.###,##") {
                locale = QLocale(QLocale::German);
                value = locale.toString(value.toDouble(), 'f', precision);
            }
        }
    }
    return value;
}

void QtRPT::fillListOfValue(QDomNode n) {
    QDomNode c = n.firstChild();
    while(!c.isNull()) {
        QDomElement e = c.toElement(); // try to convert the node to an element.
        if (!e.isNull() && e.tagName() == "TContainerField" && isFieldVisible(e)) {
            if (e.attribute("type","label") == "label") { //NOT Proccess if field set as ImageField
                QString txt = sectionField(n,e.attribute("value"),false,true);
            }
        }
        c = c.nextSibling();
    }
}

QVariant QtRPT::processFunctions(QString value) {
    if (value.contains("Date"))
        return QDate::currentDate().toString("dd.MM.yyyy");
    if (value.contains("Time"))
        return QTime::currentTime().toString();
    if (value.contains("Page"))
        return QString::number(curPage);
    if (value.contains("TotalPages"))
        return QString::number(totalPage);
    if (value.contains("LineNo")) {
        int recNo;
        if (!listOfGroup.isEmpty()) //group processing
            recNo = mg_recNo;
        else //usuall processing
            recNo = m_recNo+1;
        return QString::number(recNo);
    }
    return QVariant();
}

QImage QtRPT::sectionFieldImage(QString value) {
    return sectionValueImage(value);
}

QString QtRPT::sectionValue(QString paramName) {
    QVariant paramValue;
    paramName.replace("[","");
    paramName.replace("]","");
    //callbackFunc(recNo, paramName, paramValue);
    //if (paramValue.isNull())
    const int _recNo = m_recNo;  //bug fix to prevent change in user application
    emit setValue(m_recNo, paramName, paramValue, m_pageReport);
    m_recNo = _recNo;
    return paramValue.toString();
}

QImage QtRPT::sectionValueImage(QString paramName) {
    QImage *paramValue;
    paramName.replace("[","");
    paramName.replace("]","");
    paramValue = new QImage();
    //paramValue = new QImage(500,500,QImage::Format_ARGB32);
    emit setValueImage(m_recNo, paramName, *paramValue, m_pageReport);
    return *paramValue;
}

/*void QtRPT::setCallbackFunc( void (*func)(int &recNo, QString &paramName, QVariant &paramValue) ) {
    callbackFunc=func;
}*/

void QtRPT::printPDF(const QString &filePath, bool open) {
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printPreview(&printer);
    if (open)
        QDesktopServices::openUrl(QUrl("file:"+filePath));
#endif
}

void QtRPT::printExec(bool maximum, bool direct, QString printerName) {
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    if (!printerName.isEmpty() && !printerName.isNull()) {
        printer.setPrinterName(printerName);
        if (!printer.isValid())
            printer.setPrinterName(QPrinterInfo::defaultPrinter().printerName());
            //printer.setPrinterName(QPrinterInfo::defaultPrinterName());
    }

    if (!direct) {
        QPrintPreviewDialog preview(&printer, this, Qt::Window);

        if (maximum) {
            QList<QPrintPreviewWidget *> list = preview.findChildren<QPrintPreviewWidget *>();
            if(!list.isEmpty()) // paranoiac safety check
                list.first()->setZoomMode(QPrintPreviewWidget::FitToWidth);
        }

        connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
        //preview.setWindowState(Qt::WindowMaximized); //Qt BUG https://bugreports.qt-project.org/browse/QTBUG-14517
        QRect geom = QApplication::desktop()->availableGeometry();
        geom.setTop(30);
        geom.setLeft(5);
        geom.setHeight(geom.height()-6);
        geom.setWidth(geom.width()-6);
        preview.setGeometry(geom);

        pr = preview.findChild<QPrintPreviewWidget *>();
        lst = preview.findChildren<QAction *>();
        preview.addActions(lst);
        pr->installEventFilter(this);
        //curPage = 1;
        preview.exec();
    } else
        printPreview(&printer);  ///print without preview dialog
#endif
}

bool lessThan(const AggregateValues a, const AggregateValues b) {
    if (a.paramValue.toString() == b.paramValue.toString())
        return a.lnNo < b.lnNo;
    else
        return a.paramValue.toString() < b.paramValue.toString();
}

void QtRPT::printPreview(QPrinter *printer) {
#ifdef QT_NO_PRINTER
    Q_UNUSED(printer);
#else
    setPageSettings(printer,0);
    painter.begin(printer);
    painter.setRenderHint(QPainter::Antialiasing,true);
    fromPage = printer->fromPage();
    toPage =   printer->toPage();

    /*Make a two pass report
     *First pass calculate total pages
     *Second pass draw a report
     */
    curPage = 1;
    for (int i = 0; i < xmlDoc->documentElement().childNodes().count(); i++) {
        openDataSource(i);
        //listOfPair.clear();
        listIdxOfGroup.clear();
        m_recNo = 0;
        m_pageReport = i;
        //First pass
        processReport(printer,false,i);
        totalPage = curPage;
    }

    m_orientation = 0;
    painter.resetTransform();
    //setPageSettings(printer,0);
    curPage = 1;
    for (int i = 0; i < xmlDoc->documentElement().childNodes().count(); i++) {
        //listOfPair.clear();
        listIdxOfGroup.clear();
        m_recNo = 0;
        m_pageReport = i;
        //Second pass
        processReport(printer,true,i);
    }

    painter.end();
    //pr->setWindowState(pr->windowState() ^ Qt::WindowFullScreen);
#endif
}

void QtRPT::setPageSettings(QPrinter *printer, int pageReport) {
    QDomElement docElem = xmlDoc->documentElement().childNodes().at(pageReport).toElement();
    ph = docElem.attribute("pageHeight").toInt();
    pw = docElem.attribute("pageWidth").toInt();
    ml = docElem.attribute("marginsLeft").toInt();
    mr = docElem.attribute("marginsRight").toInt();
    mt = docElem.attribute("marginsTop").toInt();
    mb = docElem.attribute("marginsBottom").toInt();
    int orientation = docElem.attribute("orientation").toInt();

    QSizeF paperSize;
    paperSize.setWidth(pw/4);
    paperSize.setHeight(ph/4);
    if (printer->printerState() != QPrinter::Active) {
        if (orientation == 1) {
            paperSize.setWidth(ph/4);
            paperSize.setHeight(pw/4);
        }
        printer->setPaperSize(paperSize,QPrinter::Millimeter);
    }
    printer->setPageMargins(ml/4+0.01, mt/4+0.01, mr/4+0.01, mb/4+0.01, QPrinter::Millimeter);
    //qDebug()<<ph<<' '<<pw<<' '<<pageReport;

    if (m_orientation != orientation) {
        m_orientation = orientation;
        //painter.resetTransform();
        if (orientation == 1) {
            painter.rotate(90); // поворачиваем относительно (0,0)
            painter.translate(0, -painter.viewport().width()); // смещаемся на ширину вьюпорта влево
        }
    }

    QRect r = printer->pageRect();
    //painter.drawRect(0,0,r.width(),r.height());   //Rect around page
    koefRes_h = static_cast<double>(r.height()) / (ph - mt - mb);
    koefRes_w = static_cast<double>(r.width())  / (pw - ml - mr);
    if (orientation == 1) {
        koefRes_h = static_cast<double>(r.width()) / (ph - mt - mb);
        koefRes_w = static_cast<double>(r.height())  / (pw - ml - mr);
    }
    reportTitle = getBand(ReportTitle, docElem);
    pageHeader = getBand(PageHeader, docElem);
    pageFooter = getBand(PageFooter, docElem);
    masterFooter = getBand(MasterFooter, docElem);
    reportSummary = getBand(ReportSummary, docElem);
    masterData = getBand(MasterData, docElem);
    masterHeader = getBand(MasterHeader, docElem);
    dataGroupHeader = getBand(DataGroupHeader, docElem);
    dataGroupFooter = getBand(DataGroupFooter, docElem);
}

void QtRPT::processReport(QPrinter *printer, bool draw, int pageReport) {
    setPageSettings(printer, pageReport);
    int y = 0;

    drawBackground(painter);
    if (pageReport > 0) {
        newPage(printer, y, draw, true);
    } else {
        processRTitle(y,draw);
        processPHeader(y,draw);
    }

    //processRTitle(y,draw);
    //processPHeader(y,draw);

        //processMHeader(y,draw);
        //processPFooter(draw);
    prcessGroupHeader(printer,y,draw,pageReport);
        //processMasterData(printer,y,draw,pageReport);
        //processMFooter(printer,y,draw);

    processRSummary(printer,y,draw);
}

bool QtRPT::eventFilter(QObject *obj, QEvent *e) {
    if (obj == pr && e->type()==QEvent::Show)  {
        for (int i = 0; i < lst.size(); i++) {
            if (lst.at(i)->text().contains("Previous page", Qt::CaseInsensitive))
                lst.at(i)->trigger();
        }

        pr->setCurrentPage(0);
        return true;
    }
    return QWidget::eventFilter(obj,e);
}

bool QtRPT::allowPrintPage(bool draw, int curPage_) {
    if (draw) {
        if (curPage_ < fromPage )
            draw = false;
        if ((toPage!=0) && (curPage_ > toPage ))
            draw = false;
        return draw;
    } else return false;
}

bool QtRPT::allowNewPage(bool draw, int curPage_) {
    if (draw) {
        if (curPage-fromPage < 0) return false;
        if (curPage_ < fromPage )
            draw = false;
        if ((toPage!=0) && (curPage_ > toPage ))
            draw = false;
        return draw;
    } else return false;
}

void QtRPT::newPage(QPrinter *printer, int &y, bool draw, bool newReportPage) {
    //curPage += 1;
    if (allowNewPage(draw, curPage+1)) {
        printer->newPage();        
        drawBackground(painter);
    }
    curPage += 1;
    y = 0;
    if (newReportPage)            //
        processRTitle(y,draw);    //
    processPHeader(y,draw);
    processPFooter(draw);
}

void QtRPT::setBackgroundImage(QPixmap image) {
    m_backgroundImage = &image;
}

void QtRPT::drawBackground(QPainter &painter) {
    painter.setBackgroundMode(Qt::TransparentMode);
    if (m_backgroundImage != 0) {
        painter.drawPixmap(-ml*koefRes_w,
                           -mt*koefRes_h,
                           pw*koefRes_w,
                           ph*koefRes_h, *m_backgroundImage);
    }
}

void QtRPT::prcessGroupHeader(QPrinter *printer, int &y, bool draw, int pageReport) {
    m_recNo = 0;
    if (dataGroupHeader.isNull()) {

        processMHeader(y,draw);
        processPFooter(draw);
        processMasterData(printer,y,draw,pageReport);
        processMFooter(printer,y,draw);
    } else {
        fillListOfValue(masterData);
        if (listOfPair.size() > 0) {
            QDomElement e  = dataGroupHeader.toElement();
            QDomElement e1 = dataGroupFooter.toElement();
            QString groupingField = e.attribute("groupingField");

            for (int i = 0; i < recordCount.at(pageReport); i++) {
                m_recNo = i;                
                sectionField(e, groupingField, false, true);
            }

            listOfGroup.clear();
            mg_recNo = 0;

            if (masterHeader.toElement().attribute("showInGroup").toInt() == 0)
                processMHeader(y,draw);

            int grpNo = 0;
            for (int j = 0; j < listOfPair.size(); ++j) {
                if (listOfPair.at(j).pageReport == pageReport && listOfPair.at(j).paramName == groupingField) {
                    bool founded = false;
                    for (int i=0; i < listOfGroup.size(); ++i) {
                        if (listOfGroup.at(i) == listOfPair.at(j).paramValue)
                            founded = true;
                    }

                    listIdxOfGroup.clear();
                    for (int k=0; k < listOfPair.size(); ++k) {
                        if (listOfPair.at(k).paramName == groupingField &&
                            listOfPair.at(k).pageReport == pageReport &&
                            listOfPair.at(k).paramValue.toString() == listOfPair.at(j).paramValue.toString()
                           ) {
                            //fill the idx for current group
                            listIdxOfGroup << listOfPair.at(k).lnNo;
                        }
                    }

                    if (!founded) { //Start new group
                        grpNo += 1;
                        listOfGroup << listOfPair.at(j).paramValue.toString();

                        if (e.attribute("startNewPage").toInt() == 1 && grpNo != 1) //Start new page for each Data group
                            newPage(printer, y, draw);

                        m_recNo = listOfPair.at(j).lnNo;

                        //Start new numeration for group
                        if (e.attribute("startNewNumeration").toInt() != 0)
                            mg_recNo = 0;
                        if (allowPrintPage(draw,curPage))  //Draw header of the group
                            drawBandRow(dataGroupHeader,y);
                        y += e.attribute("height").toInt();

                        if (masterHeader.toElement().attribute("showInGroup").toInt() == 1)
                            processMHeader(y,draw);
                        processPFooter(draw);
                        processMasterData(printer,y,draw,pageReport);
                        if (masterFooter.toElement().attribute("showInGroup").toInt() == 1)
                            processMFooter(printer,y,draw);
                        //---
                        m_recNo = listOfPair.at(j).lnNo;
                        if (allowPrintPage(draw,curPage)) { //Draw footer of the group
                            drawBandRow(dataGroupFooter,y);
                        }
                        y += e1.attribute("height").toInt();
                    }
                }
            }
            if (masterFooter.toElement().attribute("showInGroup").toInt() == 0)
                processMFooter(printer,y,draw);
        }
    }
}

void QtRPT::processMasterData(QPrinter *printer, int &y, bool draw, int pageReport) {
    if (!recordCount.isEmpty()) {
        if (pageReport < recordCount.size() && recordCount.at(pageReport) > 0) {
            if (!masterData.isNull()) {
                for (int i = 0; i < recordCount.at(pageReport); i++) {
                    m_recNo = i;

                    bool founded = false;
                    if (listIdxOfGroup.size() > 0) { //If report with groups, we checking that current line in the current group
                        for (int k = 0; k < listIdxOfGroup.size(); k++) {
                            if (listIdxOfGroup.at(k) == i)
                                founded = true;
                        }
                    } else {
                        founded = true;
                    }

                    if (founded) {
                        mg_recNo += 1;
                        int yPF = 0;
                        if (!pageFooter.isNull()) {
                            QDomElement pf = pageFooter.toElement();
                            yPF = pf.attribute("height").toInt();
                        }

                        int yMF = 0;
                        if (!masterFooter.isNull()) {
                            QDomElement mf = masterFooter.toElement();
                            yMF = mf.attribute("height").toInt();
                        }

                        QDomElement e = masterData.toElement();
                        drawBandRow(masterData,y,false);
                        if (y + e.attribute("realHeight").toInt() > ph-mb-mt-yPF-yMF) {
                            newPage(printer, y, draw);
                            processMHeader(y,draw);
                        }

                        if (allowPrintPage(draw,curPage)) drawBandRow(masterData,y,true);
                        else fillListOfValue(masterData);
                        y += e.attribute("realHeight").toInt();
                    }
                }
            }
        }
    }
}

void QtRPT::processMHeader(int &y, bool draw) {
    if (masterHeader.isNull()) return;
    QDomElement e = masterHeader.toElement();
    if (allowPrintPage(draw,curPage)) drawBandRow(masterHeader,y);
    y += e.attribute("height").toInt();
    //painter.drawLine(0,y*koefRes_h,r.width(),y*koefRes_h);
}

void QtRPT::processRTitle(int &y, bool draw) {
    if (reportTitle.isNull()) return;
    QDomElement e = reportTitle.toElement();
    if (allowPrintPage(draw,curPage)) drawBandRow(reportTitle,y);
    y += e.attribute("height").toInt();
    //painter.drawLine(0,y*koefRes_h,r.width(),y*koefRes_h);
}

void QtRPT::processPHeader(int &y, bool draw) {
    if (pageHeader.isNull()) return;
    QDomElement e = pageHeader.toElement();
    if (allowPrintPage(draw,curPage)) {
        drawBandRow(pageHeader,y);
    }
    y += e.attribute("height").toInt();
    //painter.drawLine(0,y*koefRes_h,pw*koefRes_h,y*koefRes_h);
}

void QtRPT::processMFooter(QPrinter *printer, int &y, bool draw) {
    if (masterFooter.isNull()) return;
    QDomElement e = masterFooter.toElement();
    if (y > ph-mb-mt-e.attribute("height").toInt())
        newPage(printer, y, draw);
    if (allowPrintPage(draw,curPage)) drawBandRow(masterFooter,y);
    y += e.attribute("height").toInt();
}

void QtRPT::processPFooter(bool draw) {
    if (pageFooter.isNull()) return;
    QDomElement e = pageFooter.toElement();
    int y1 = ph-mb-mt-e.attribute("height").toInt();
    if (allowPrintPage(draw,curPage)) drawBandRow(pageFooter,y1);
    //painter.drawLine(0,y1*koefRes_h,pw*koefRes_h,y1*koefRes_h);
}

void QtRPT::processRSummary(QPrinter *printer, int &y, bool draw) {
    if (reportSummary.isNull()) return;
    QDomElement e = reportSummary.toElement();
    if (y + e.attribute("height").toInt() > ph-mb-mt-e.attribute("height").toInt())
        newPage(printer, y, draw);
    if (allowPrintPage(draw,curPage)) drawBandRow(reportSummary,y);
    y += e.attribute("height").toInt();
    //painter.drawLine(0,y*koefRes_h,pw*koefRes_h,y*koefRes_h);
}

void QtRPT::openDataSource(int pageReport) {
    QDomElement docElem = xmlDoc->documentElement().childNodes().at(pageReport).toElement();
    QDomNode n = docElem.firstChild();
    QDomElement dsElement;
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        if ((!e.isNull()) && (e.tagName() == "DataSource")) {
            dsElement = e;
        }
        n = n.nextSibling();
    }

    if (!dsElement.isNull() && dsElement.attribute("type") == "SQL") {
        QString dsName = dsElement.attribute("name");
        QString dbType = dsElement.attribute("dbType");
        QString dbName = dsElement.attribute("dbName");
        QString dbHost = dsElement.attribute("dbHost");
        QString dbUser = dsElement.attribute("dbUser");
        QString dbPassword = dsElement.attribute("dbPassword");
        QString dbCoding = dsElement.attribute("dbCoding");
        QString charsetCoding = dsElement.attribute("charsetCoding");
        QString sqlQuery = dsElement.text().trimmed();
        rptSql = new RptSql(dbType,dbName,dbHost,dbUser,dbPassword,this);
        rptSql->setObjectName(dsName);
        if (!rptSql->openQuery(sqlQuery,dbCoding,charsetCoding)) {
            recordCount << 0;
            return;
        }

        recordCount << rptSql->getRecordCount();
    }
}

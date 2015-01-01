/*
Name: QtRpt
Version: 1.4.4
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef QTRPTNAMESPACE_H
#define QTRPTNAMESPACE_H
#include <QObject>
#include <QMetaType>
namespace QtRptName {
    enum BandType {
        ReportTitle,
        PageHeader,
        DataGroupHeader,
        MasterHeader,
        MasterData,
        MasterFooter,
        DataGroupFooter,
        ReportSummary,
        PageFooter
    };

    enum FieldType {
        Text,
        TextImage,
        TextRich,
        Image,
        Diagram,
        Reactangle,
        RoundedReactangle,
        Circle,
        Triangle,
        Rhombus,
        Line,
        Barcode
    };

    enum BorderStyle {
        Dashed,
        Dot_dash,
        Dot_dot_dash,
        Dotted,
        Double,
        Groove,
        Inset,
        Outset,
        Ridge,
        Solid,
        BorderNone
    };

    enum Command {
        None,
        Name,
        Bold,
        Italic,
        Underline,
        Strikeout,
        Font,
        FontSize,
        FontColor,
        FontName,
        Frame,
        FrameLeft,
        FrameRight,
        FrameTop,
        FrameBottom,
        FrameNo,
        FrameAll,
        FrameStyle,
        FrameWidth,
        AligmentH,
        AligmentV,
        Left,
        Top,
        Width,
        Height,
        Length,
        BackgroundColor,
        BorderColor,
        Printing,
        StartNewNumeration,
        ShowInGroup,
        StartNewPage,
        AutoHeight,
        ArrowStart,
        ArrowEnd,
        IgnoreRatioAspect,
        BarcodeType,
        BarcodeFrameType
    };


}

Q_DECLARE_METATYPE(QtRptName::FieldType)



//Q_ENUMS(QtRptName::FieldType)

//qRegisterMetaType<QtRptName::FieldType>( "FieldType" );

//qRegisterMetaTypeStreamOperators()

#endif // QTRPTNAMESPACE_H

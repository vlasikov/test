#include "createpdf.h"

#include <QTextDocument>
#include <QPrinter>
#include <QTextCodec>


void CreatePdf::print(QString *html)
{
    QTextDocument document;
    document.setHtml(*html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("result.pdf");
    printer.setPageMargins(QMarginsF(1, 1, 1, 1));

    document.print(&printer);
}


/*
 *
 *  This is the library of mathematical expressions.
 *  Template use double by default.
 *
 *  !!!You must declare all operators in class T that you want to use!!!
 *
 *  !!!You must add your own operations to QOperation::getAllOperationList if tou want to use it!!!
 *
 *  !!!You must declare T::operator double () to use your own class!!!
 *
 *
 * */


/*  FIXIT:
 *
 *
 * */

#pragma once

#ifndef QOPERATION_H
#define QOPERATION_H

#include <QtCore>
#include <QChar>
#include <math.h>
#include <algorithm>
#include <typeinfo>
#include <QString>
#include <stdlib.h>
#include <qptrvector.h>
#include <QPaintDevice>
#include <QPainter>
#include <QTextLayout>

namespace // unnamed namespace
{

#define DEFAULT_MATH_FOLDER_PATH QString(":/math/")
#define DEFAULT_OPERATION_SYNONYMS_FILE_NAME QString("opsynonyms.txt")

// Associativity of operation
namespace QOperationAssociativity
{
    const uint leftToRight = 0;
    const uint rightToLeft = 1;
}

namespace OptimizeFlags
{
    const uint CONST_OPTIMIZATION      = 1 << 0;
    const uint SPECIAL_OPTIMIZATION    = 1 << 1;
    const uint POLYNOMIAL_OPTIMIZATION = 1 << 2;
    const uint DEFAULT_OPTIMIZATION = CONST_OPTIMIZATION | SPECIAL_OPTIMIZATION |
            POLYNOMIAL_OPTIMIZATION;
    const uint NO_OPTIMIZATION = 0;
}

namespace CompilationFlags
{
    const uint ALLOW_VARIABLES                = 1 <<  0;
    const uint ALLOW_CONSTANTS                = 1 <<  1;
    const uint ALLOW_LITERAL_CONSTANTS        = 1 <<  2;
    const uint ALLOW_COMMON_OPERATIONS        = 1 <<  3;
    const uint ALLOW_POWER_OPERATIONS         = 1 <<  4;
    const uint ALLOW_SIGN_OPERATIONS          = 1 <<  5;
    const uint ALLOW_INTEGER_OPERATIONS       = 1 <<  6;
    const uint ALLOW_TRIGONOMETRIC_OPERATIONS = 1 <<  7;
    const uint ALLOW_LOGARITHM_OPERATIONS     = 1 <<  8;
    const uint ALLOW_LOGIC_OPERATIONS         = 1 <<  9;
    const uint ALLOW_BIT_OPERATIONS           = 1 << 10;
    const uint ALLOW_HYPERBOLIC_OPERATIONS    = 1 << 11;
    const uint ALLOW_SQARE_BRACKETS           = 1 << 12;
    const uint ALLOW_CURLY_BRACKETS           = 1 << 13;
    const uint ALLOW_ROUND_BRACKETS           = 1 << 14;
    const uint ALLOW_FLOAT_OPERATIONS         = 1 << 15;
    const uint ALLOW_UNSIGNED_MULTIPLICATION  = 1 << 16;
    const uint STRICT_SYNTAX                  = 1 << 17;
    const uint LITERAL_CONSTANT_AS_VARIABLE   = 1 << 18;

    const uint DEFAULT_COMPILATION_FLAGS =
            ALLOW_VARIABLES | ALLOW_CONSTANTS | ALLOW_LITERAL_CONSTANTS |
            ALLOW_COMMON_OPERATIONS | ALLOW_POWER_OPERATIONS | ALLOW_SIGN_OPERATIONS |
            ALLOW_INTEGER_OPERATIONS | ALLOW_TRIGONOMETRIC_OPERATIONS | ALLOW_LOGARITHM_OPERATIONS |
            ALLOW_LOGIC_OPERATIONS | ALLOW_BIT_OPERATIONS | ALLOW_HYPERBOLIC_OPERATIONS |
            ALLOW_SQARE_BRACKETS | ALLOW_CURLY_BRACKETS | ALLOW_ROUND_BRACKETS |
            ALLOW_FLOAT_OPERATIONS | !ALLOW_UNSIGNED_MULTIPLICATION | !STRICT_SYNTAX;

    const uint DEFAULT_DOUBLE_COMPILATION_FLAGS =
            ALLOW_VARIABLES | ALLOW_CONSTANTS | ALLOW_LITERAL_CONSTANTS | ALLOW_COMMON_OPERATIONS |
            ALLOW_POWER_OPERATIONS | ALLOW_SIGN_OPERATIONS | ALLOW_TRIGONOMETRIC_OPERATIONS |
            ALLOW_LOGARITHM_OPERATIONS | ALLOW_LOGIC_OPERATIONS | ALLOW_HYPERBOLIC_OPERATIONS |
            ALLOW_SQARE_BRACKETS | ALLOW_CURLY_BRACKETS | ALLOW_ROUND_BRACKETS |
            ALLOW_FLOAT_OPERATIONS | !LITERAL_CONSTANT_AS_VARIABLE;
}

namespace OperationToStringConvertionFlags
{
    const uint ALLOW_BINAR_SPACE_SEPARATION  = 1 <<  0;
    const uint ALLOW_UNAR_SPACE_SEPARATION   = 1 <<  1;
    const uint ALLOW_UNSIGNED_MULTIPLICATION = 1 <<  2;

    const uint DEFAULT_CONVERTION_FLAGS =
            ALLOW_BINAR_SPACE_SEPARATION | ALLOW_UNAR_SPACE_SEPARATION |
            !ALLOW_UNSIGNED_MULTIPLICATION;
}

namespace DrawingFlags
{
    const uint DRAW_RADICAL               = 1 << 0;
    const uint DRAW_SLASH_FRACTION        = 1 << 1;
    const uint ONLY_SIMPLE_FRACTION_SLASH = 1 << 2;
    const uint DRAW_POWER_IN_SUPERSCRIPT  = 1 << 3;
    const uint DRAW_VARIABLE_SUBSCRIPT    = 1 << 4;
    const uint BINAR_SPACE_SEPARATION     = 1 << 5;
    const uint UNAR_SPACE_SEPARATION      = 1 << 6;

    const uint DEFAULT_DRAWING_FLAGS =
            DRAW_RADICAL | !DRAW_SLASH_FRACTION | ONLY_SIMPLE_FRACTION_SLASH |
            DRAW_POWER_IN_SUPERSCRIPT | DRAW_VARIABLE_SUBSCRIPT | !BINAR_SPACE_SEPARATION |
            !UNAR_SPACE_SEPARATION;
}

// General class that works with math expressions
template <class T> class QFunction;

// Class of function variables
template <class T> class QFunctionVariable;

// Slave which is used in compilation
template <class T> struct QStackUnit;

// Class of QOperation <T> pointers
template <class T> class QOperationPtrVector;

// Common classes
//
template <class T> class QOperationCompiler;
class QOperationContext;

    // Fundamental class to all simple operations.
template <class T> class              QOperation;
    // Fundamental class to all binar operations.
template <class T> class         QBinarOperation;
    // Fundamental class to all binar operations with sign between two operands.
template <class T> class  QBinarOperandOperation;
    // Fundamental class to all binar functions like "f(a, b)"
template <class T> class QBinarFunctionOperation;
    // Fundamental class to all unar operations.
template <class T> class          QUnarOperation;
    // Funcdamental class to all unar operations with operation before operand "f(T)" == "fT"
template <class T> class    QUnarPrefixOperation;
    // Operands
template <class T> class         QConstOperation; // Numeric const
template <class T> class           QVarOperation; // Literal variable
    // Common operations
template <class T> class           QNegOperation; // Unar minus == negation
template <class T> class           QSumOperation; // Addition
template <class T> class           QSubOperation; // Subtraction
template <class T> class           QMulOperation; // Multiplication
template <class T> class           QDivOperation; // Division
    // Power operations
template <class T> class          QSqrtOperation; // Square root
template <class T> class           QPowOperation; // Raising to a power "^"
template <class T> class           QExpOperation; // Exponent
template <class T> class          QRootOperation; // Root: root(x, y) = pow(x, 1 / y)
    // Sign operations
template <class T> class          QSignOperation; // Sign
template <class T> class           QAbsOperation; // Absolute
    // Integer operations
template <class T> class         QRoundOperation; // Rounding
template <class T> class         QTruncOperation; // Truncation
template <class T> class          QCeilOperation; // Ceil
template <class T> class         QFractOperation; // Fractional part
template <class T> class           QModOperation; // Modular division
    // Trigonometrics
template <class T> class           QSinOperation; // Sine
template <class T> class           QCosOperation; // Cosine
template <class T> class            QTgOperation; // Tangent
template <class T> class           QCtgOperation; // Cotangent
template <class T> class           QSecOperation; // Secant
template <class T> class         QCosecOperation; // Cosecant
template <class T> class        QArcsinOperation; // Arcsine
template <class T> class        QArccosOperation; // Arccosine
template <class T> class         QArctgOperation; // Arctangent
template <class T> class        QArcctgOperation; // Arccotangent
    // Logarithms
template <class T> class            QLnOperation; // Natural logarithm
template <class T> class            QLgOperation; // Decimal logarithm
template <class T> class            QLbOperation; // Binary logarithm
template <class T> class           QLogOperation; // Logaritmg like: "log(x, y)" = "ln(x)/ln(y)"
    // Logic
template <class T> class           QNotOperation; // Logic negation
template <class T> class          QLessOperation; // Less operation "<"
template <class T> class         QEqualOperation; // Equality operation "="
template <class T> class          QOverOperation; // Greater operation ">"
template <class T> class       QNotoverOperation; // Not greater operation "<="
template <class T> class       QNotlessOperation; // Not less operation ">="
template <class T> class      QNotequalOperation; // Not equal operation "!="
template <class T> class            QOrOperation; // Logic "or" "||"
template <class T> class           QAndOperation; // Logic "and" "&&"
template <class T> class           QXorOperation; // Logic XOR
    // Bit operations
template <class T> class          QBnotOperation; // Bit inversion
template <class T> class           QBorOperation; // Bit "or"  "|"
template <class T> class          QBandOperation; // Bit "and" "&"
template <class T> class          QBxorOperation; // Bit "xor" "^^"
template <class T> class          QBlshOperation; // Left  bit shift "<<"
template <class T> class          QBrshOperation; // Right bit shift ">>"
    // Hyperbolic operations
template <class T> class          QSinhOperation; // Hiperbolic sine
template <class T> class          QCoshOperation; // Hyperbolic cosine
template <class T> class           QTghOperation; // Hyperbolic tangent
template <class T> class          QCtghOperation; // Hyperbolic cotangent
template <class T> class          QSechOperation; // Hyperbolic secant
template <class T> class        QCosechOperation; // Hyperbolic cosecant
template <class T> class         QAsinhOperation; // Hyperbolic arcsine
template <class T> class         QAcoshOperation; // Hyperbolic arccosine
template <class T> class          QAtghOperation; // Hyberbolic arctangent
template <class T> class        QArctghOperation; // Hyperbolic arccotangent
// End of common classes

// Functions
template <class T>
void clearQVector(QVector<T *> &vect);

inline bool doubleCmp(const double &d1, const double &d2);

template <class T>
void clearQStack(QStack <QStackUnit <T> > &stack);
// End of functions

template <class T>
struct QStackUnit
{
    QOperation <T> *op; // Any operation in string
    int brackets; // Number of (opening - closing) brackets before operation
}; // End of QStackUnit

template <class T>
class QOperationPtrVector
{
public:
    QOperationPtrVector();
    ~QOperationPtrVector();
    void push_back(QOperation <T> *member);
    const QOperation <T> *operator[](int num) const {return m_vector[num]; }
    QOperationPtrVector<T> &operator =(const QOperationPtrVector <T> &other);
    void clear();
    int length() const {return m_vector.length(); }

private:
    QVector < QOperation <T> *> m_vector;

};

template <class T>
class QOperation
{
    friend class QFunction <T>;

public:
    virtual ~QOperation();
    virtual T getResult() const = 0; // Returns the result of the operation.
    //      Returns pointer to operation that starts from s[pos] and moves pos to the next symbol
    // after operation. Returns nullptr if no operations start here.
    virtual QOperation <T> *getOperationFromString(const QString &functionString, int &firstSymbolPos,
                          const QOperationCompiler<T> &compiler) const;
    //      Return true if this operation starts from s[pos].
    /*virtual bool operationStartsHere(const QString &functionString, int &firstSymbolPos,
                          const QOperationCompiler<T> &compiler) const;*/
    //      Initialize this operation from s and moves pos to the next symbol after operation.
    //      Returns synonyms of this operation. synonyms()[0] is the common name of the operation.
    virtual QVector <QString> getDefaultSynonyms() const = 0;
    virtual uint getDefaultAssociativity() const; // Returns associativity of this operation
    virtual int getDefaultPriority() const = 0; // Returns the priority of this operation.
    //      Connects all links from variable operations to variables
    virtual void addVariablesToList(QFunction<T> &func) = 0;
    virtual void connectVarLinks(QFunctionVariable <T> *variable) = 0;
    //      Returns operation that was token from the string. Returns nullptr if functionstring
    // is a wrong expression and returns to errorPos the (position + 1) of mistake if it can be
    // established.
    //      Initialize as many arguments as need from stack. Returns -1 if smth went wrong
    virtual int compileFromStack(QStack <QStackUnit <T> > &stack) = 0;
    static bool isOpeningBracket(const QChar &ch); // Returns true if ch is opening bracket
    static bool isClosingBracket(const QChar &ch); // Returns true if ch is closing bracket
    //      Processes string with this operation features before compiling
    virtual int prepareQString(QString &s, const QOperationCompiler<T> &compiler) const;
    virtual QString toQString(const QOperationCompiler<T> &compiler) const = 0;
    virtual QOperation<T> *getCopy() const = 0;
    //virtual QOperation <T> *getCopy(QFunction <T> &parentFunction) const = 0;
    virtual QOperation <T> *getDerivative(const QString &argName,
                                          QFunction <T> &parentFunction) const = 0;
    //      Returns true if this operation is coonst and can be replaced by const operation
    virtual bool isAlwaysConstant() const = 0;
    virtual QOperation <T> *optimizeIfConstant(QFunction <T> &parentFunction);
    virtual QOperation <T> *optimizeSpecial(QFunction <T> &parentFunction);
    virtual void makeSumPolynomial(QVector <QOperation <T> *> &positive,
                                   QVector <QOperation <T> *> &negative);
    virtual QOperation <T> *optimizePolynomial(QFunction <T> &parentFunction);
    QOperation <T> *optimize(QFunction <T> &function,
                             uint optimizeFlags = OptimizeFlags::DEFAULT_OPTIMIZATION);
    virtual bool isBinaryFunctionOperation() const;
    virtual QString name() const; // Returns the operation name
    virtual int getArgumentNum() const;
    virtual int draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                     const QPoint &bottomLeft, int height, bool inBrackets = false) const = 0;
    virtual int getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                bool inBrackets) const = 0;

    static const char FLOATING_POINT = '.';

    //      Standart priorities of operations and brackets
    static const int CONST_OPERATION_PRIORITY = 1e6,
              BRACKETS_PRIORITY        =  15;

protected:

    static const char OPENING_BRACKET = '(',
                      CLOSING_BRACKET = ')';

    static const char BINARY_OPERATION_DELIM = ',';

}; // End of QOperation.

class QOperationContext
{
public:
    QOperationContext();
    template <class T> QOperationContext(const QOperation <T> *operation);
    void setPriority(int priority) {m_priority = priority; }
    void setAssociativity(uint associativity) {m_associativity = associativity; }
    void setSynonyms(const QVector <QString> &synonyms) {m_synonyms = synonyms; }
    void setDrawingName(const QString &s) {m_drawingName = s; }
    void setDrawingColor(const QColor &color) {m_drawingColor = color; }
    int getPriority() const {return m_priority; }
    uint getAssociativity() const {return m_associativity; }
    const QVector <QString> &getSynonyms() const {return m_synonyms; }
    const QString &getDrawingName() const {return m_drawingName; }
    const QColor &getDrawingColor() const {return m_drawingColor; }

private:
    int m_priority;
    uint m_associativity;
    QVector <QString> m_synonyms;
    QString m_drawingName;
    QColor m_drawingColor;
};

template <class T>
class QOperationCompiler
{
public:
    QOperationCompiler();
    QOperationCompiler(uint compilationFlags, uint optimizationFlags, uint convertionToStringFlags);
    ~QOperationCompiler();
    const QMap <QString, QOperationContext> &getContextMap() const {return m_operationContextMap; }
    uint getCompilationFlags() const {return m_compilationFlags; }
    uint getDefaultCompilationFlags() const;
    uint getOptimizationFlags() const;
    int initContextFromFile(QString path = DEFAULT_MATH_FOLDER_PATH + DEFAULT_OPERATION_SYNONYMS_FILE_NAME);
    QOperation <T> *compile(QString &functionString, QFunction <T> &parentFunction,
                            int &errorPos = nullptr) const;
    int prepareString(QString &s) const;
    bool isOpeningBracket(QChar s) const;
    bool isClosingBracket(QChar s) const;
    const QOperationPtrVector <T> &getAllOperationList() const;
    int getOperationNumber() const;
    QOperation <T> *getOperationFromString(const QString &functionString, int &firstSymbolPos) const;
    void setCompilationFlags(uint flags);
    void setConvertionToStringFlags(uint flags);
    void setOptimizationFlags(uint flags);
    void setDrawingFlags(uint flags) {m_drawingFlags = flags; }
    uint getConvetionToStringFlags() const;
    uint getDrawingFlags() const;
    int getOperationPriority(const QOperation <T> *operation) const;
    uint getOperationAssociativity(const QOperation <T> *operation) const;
    const QString &getOperationMainSynonym(const QOperation <T> *operation) const;
    T getValueFromString(const QString &s, int &pos, int &ok) const;
    QChar getOpeningBracket() const {return m_openingBracket; }
    QChar getClosingBracket() const {return m_closingBracket; }
    QChar getSpaceChar() const {return m_spaceChar; }
    bool isVariableSymbol(QChar ch) const;
    bool isFirstVariableSymbol(QChar ch) const;
    const QVector<QFunctionVariable<T> > &getLiteralConstants() const {return m_literalConstants; }
    const QString &getOperationDrawingName(const QOperation<T> *op) const;
    void setDrawindBinarSpaceWidth(double w) {m_drawingBinarSpaceWidth = w; }
    void setDrawindUnarSpaceWidth(double w) {m_drawingUnarSpaceWidth = w; }
    double getDrawingBinarSpaceWidth() const {return m_drawingBinarSpaceWidth; }
    double getDrawingUnarSpaceWidth() const {return m_drawingUnarSpaceWidth; }
    void setDrawingFont(const QFont &font) {m_drawingFont = font; }
    const QFont &getDrawingFont() const {return m_drawingFont; }
    const QColor &getOperationDrawingColor(const QOperation<T> *op) const;
    void setBinarOperationDelimeter(QChar delim) {m_binaryOperationDelimeter = delim; }
    QChar getBinarOperationDelimeter() const {return m_binaryOperationDelimeter; }
    void setDoubleDrawingBase(int base) {m_doubleDrawingBase = base; }
    int  getDoubleDrawingBase() const {return m_doubleDrawingBase; }
    void setDoublePrecision(int prec) {m_doublePrecision = prec; }
    int getDoublePrecision() const {return m_doublePrecision; }

    static const QOperationCompiler<T> defaultCompiler;

private:
    QMap<QString, QOperationContext> m_operationContextMap;
    QOperationPtrVector<T> m_operations;
    QVector<QFunctionVariable<T> > m_literalConstants;
    uint m_compilationFlags;
    uint m_convertionToStringFlags;
    uint m_optimizationFlags;
    uint m_drawingFlags;
    QChar m_binaryOperationDelimeter;
    QChar m_openingBracket;
    QChar m_closingBracket;
    QChar m_spaceChar;
    QFont m_drawingFont;
    int m_doubleDrawingBase;
    int m_doublePrecision;
    double m_drawingUnarSpaceWidth; // ratio between widths of drawed space and char space
    double m_drawingBinarSpaceWidth; // ratio between widths of drawed space and char space
    static const char DEFAULT_BINARY_OPERATION_DELIMETER = ',';
    static const int CONST_OPERATION_PRIORITY = 1e6;
    void initOperationList();
    void initDefaultContext();

};

template <class T>
class QUnarOperation : public QOperation<T>
{
public:
    ~QUnarOperation();
    int compileFromStack(QStack <QStackUnit <T> > &stack);
    void addVariablesToList(QFunction<T> &func);
    virtual void connectVarLinks(QFunctionVariable<T> *variable);
    bool isAlwaysConstant() const;
    int getArgumentNum() const {return 1; }
    QOperation<T> *getCopy() const;
    virtual QOperation <T> *optimizeIfConstant(QFunction <T> &function);
    virtual QOperation <T> *optimizeSpecial(QFunction<T> &parentFunction);
    virtual QOperation <T> *optimizePolynomial(QFunction<T> &parentFunction);

protected:
    QOperation<T> *_arg;

}; // End of QUnarOperation

template <class T>
class QUnarPrefixOperation : public QUnarOperation<T>
{
public:
    QUnarPrefixOperation(QOperation <T> *arg);
    uint getDefaultAssociativity() const;
    virtual QString toQString(const QOperationCompiler<T> &compiler) const;
    virtual int getDefaultPriority() const;
    virtual int draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                     const QPoint &bottomLeft, int height, bool inBrackets = false) const;
    virtual int getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                bool inBrackets) const;

}; // End of QUnarPrefixOperation

template <class T>
class QBinarOperation : public QOperation <T>
{
public:
    QBinarOperation(QOperation<T> *arg1, QOperation<T> *arg2);
    ~QBinarOperation();
    int getArgumentNum() const {return 2; }
    int compileFromStack(QStack<QStackUnit <T> > &stack);
    void addVariablesToList(QFunction<T> &func);
    void connectVarLinks(QFunctionVariable<T> *variable);
    bool isAlwaysConstant() const;
    QOperation<T> *getCopy() const;
    virtual QOperation <T> *optimizeIfConstant(QFunction <T> &function);
    virtual QOperation <T> *optimizeSpecial(QFunction<T> &parentFunction);
    virtual QOperation <T> *optimizePolynomial(QFunction<T> &parentFunction);

protected:
    QOperation <T> *_arg1, *_arg2;

}; // End of QBinarOperation

template <class T>
class QBinarOperandOperation : public QBinarOperation <T>
{
public:
    QBinarOperandOperation(QOperation <T> *arg1, QOperation<T> *arg2);
    virtual QString toQString(const QOperationCompiler<T> &compiler) const;
    virtual int getDefaultPriority() const;
    virtual int draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                     const QPoint &bottomLeft, int height, bool inBrackets) const;
    virtual int getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                bool inBrackets) const;
    int drawString(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                   const QPoint &bottomLeft, int height, bool inBrackets) const;
    int getDrawnStringWidth(const QOperationCompiler<T> &compiler, int height,
                            bool inBrackets) const;

private:

}; // End of QBinarOperandOperation

template <class T>
class QBinarFunctionOperation : public QBinarOperation <T>
{
public:
    QBinarFunctionOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    virtual int getDefaultPriority() const;
    virtual QString toQString(const QOperationCompiler<T> &compiler) const;
    bool isBinaryFunctionOperation() const;
    virtual int draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                     const QPoint &bottomLeft, int height, bool inBrackets) const;
    virtual int getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                bool inBrackets) const;

private:

};

template <class T>
class QConstOperation : public QOperation <T>
{
public:
    QConstOperation(T value = 0);
    ~QConstOperation();
    T getResult() const;
    QString name() const {return QString("const"); } // Returns the operation's name
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    void addVariablesToList(QFunction<T> &) {}
    void connectVarLinks(QFunctionVariable<T> *) {}
    virtual QOperation <T> *getOperationFromString(const QString &functionString, int &firstSymbolPos,
                          const QOperationCompiler<T> &compiler) const;
    QOperation<T> *getCopy() const;
    int compileFromStack(QStack<QStackUnit<T> > &stack);
    QString toQString(const QOperationCompiler<T> &compiler) const;
    QOperation <T> *getCopy(QFunction<T> *function) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;
    bool isAlwaysConstant() const;
    int draw(QPaintDevice *device, const QOperationCompiler<T> &compiler, const QPoint &bottomLeft,
             int height, bool inBrackets) const;
    int getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                bool inBrackets) const;

private:
    T _value;

}; // End of QConstOperation

template <class T>
class QVarOperation : public QOperation <T>
{
public:
    QVarOperation();
    QVarOperation(const QString &name);
    QVarOperation(const QString &name, const T &value);
    ~QVarOperation();
    T getResult() const;
    QString name() const {return QString("var"); } // Returns the operation name
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    void addVariablesToList(QFunction<T> &);
    void connectVarLinks(QFunctionVariable<T> *variable);
    int compileFromStack(QStack<QStackUnit<T> > &stack);
    virtual QOperation <T> *getOperationFromString(const QString &functionString, int &firstSymbolPos,
                          const QOperationCompiler<T> &compiler) const;
    QString toQString(const QOperationCompiler<T> &compiler) const;
    QVector<QFunctionVariable<T> > getLiteralConstantList();
    QOperation<T> *getCopy() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;
    bool isAlwaysConstant() const;
    int draw(QPaintDevice *device, const QOperationCompiler<T> &compiler, const QPoint &bottomLeft,
             int height, bool inBrackets) const;
    int getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                bool inBrackets) const;

private:
    QFunctionVariable<T> *_var;
    QString _varName;

}; // End of QVarOperation

template <class T>
class QNegOperation : public QUnarPrefixOperation <T>
{
public:
    QNegOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("neg"); } // Returns the operation name
    QVector<QString> getDefaultSynonyms() const;
    virtual QOperation <T> *getOperationFromString(const QString &functionString, int &firstSymbolPos,
                          const QOperationCompiler<T> &compiler) const;
    bool operationStartsHere(const QString &s, int pos, QFunction <T> &function,
                             const QOperationCompiler<T> &compiler) const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;
    void makeSumPolynomial(QVector<QOperation<T> *> &positive,
                           QVector<QOperation<T> *> &negative);
}; // End of QNegOperation

template <class T>
class QSumOperation : public QBinarOperandOperation <T>
{
public:
    QSumOperation(QOperation<T> *arg1, QOperation<T> *arg2);
    T getResult() const;
    QString name() const {return QString("sum"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *function) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;
    QOperation <T> *optimizeSpecial(QFunction<T> &parentFunction);
    void makeSumPolynomial(QVector<QOperation<T> *> &positive, QVector<QOperation<T> *> &negative);
    QOperation <T> *optimizePolynomial(QFunction<T> &parentFunction);

private:

}; // End of QSumOperation

template <class T>
class QSubOperation : public QBinarOperandOperation <T>
{
public:
    QSubOperation(QOperation<T> *arg1, QOperation<T> *arg2);
    T getResult() const;
    QString name() const {return QString("sub"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *function) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;
    QOperation <T> *optimizeSpecial(QFunction<T> &parentFunction);
    void makeSumPolynomial(QVector<QOperation<T> *> &positive, QVector<QOperation<T> *> &negative);

}; // End of QSubOperation

template <class T>
class QMulOperation : public QBinarOperandOperation <T>
{
public:
    QMulOperation(QOperation<T> *arg1, QOperation<T> *arg2);
    T getResult() const;
    QString name() const {return QString("mul"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QString toQString() const;
    bool operationStartsHere(const QString &s, int pos, QFunction <T> &function) const;
    int prepareQString(QString &str, const QOperationCompiler<T> &compiler) const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;
    QOperation <T> *optimizeSpecial(QFunction<T> &parentFunction);

private:

}; // End of QMulOperation

template <class T>
class QDivOperation : public QBinarOperandOperation <T>
{
public:
    QDivOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("div"); }
    QVector <QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;
    QOperation <T> *optimizeSpecial(QFunction<T> &parentFunction);
/*    int draw(QPaintDevice *device, const QOperationCompiler<T> &compiler, const QPoint &bottomLeft,
             int height, bool inBrackets) const;
    int getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                bool inBrackets) const;*/


}; // End of QDivOperation

template <class T>
class QExpOperation : public QUnarPrefixOperation <T>
{
public:
    QExpOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("exp"); }
    QVector <QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // end of QExpOperation

template <class T>
class QSinOperation : public QUnarPrefixOperation <T>
{
public:
    QSinOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("sin"); }
    QVector <QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QSinOperation

template <class T>
class QCosOperation : public QUnarPrefixOperation <T>
{
public:
    QCosOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("cos"); }
    QVector <QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // Enf of QCosOperation

template <class T>
class QTgOperation : public QUnarPrefixOperation <T>
{
public:
    QTgOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("tg"); }
    QVector <QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QTgOperation

template <class T>
class QCtgOperation : public QUnarPrefixOperation <T>
{
public:
    QCtgOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("ctg"); }
    QVector <QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;
}; // End of QCtgOperation

template <class T>
class QSqrtOperation : public QUnarPrefixOperation <T>
{
public:
    QSqrtOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("sqrt"); }
    QVector <QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;
    int draw(QPaintDevice *device, const QOperationCompiler<T> &compiler, const QPoint &bottomLeft,
             int height, bool inBrackets) const;
    int getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                bool inBrackets) const;
};

template <class T>
class QSignOperation : public QUnarPrefixOperation <T>
{
public:
    QSignOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("sign"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QSignOperation

template <class T>
class QPowOperation : public QBinarOperandOperation <T>
{
public:
    QPowOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("pow"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    uint getDefaultAssociativity() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;
    QOperation <T> *optimizeSpecial(QFunction<T> &parentFunction);

}; // End of QPowOperation

template <class T>
class QRootOperation : public QBinarFunctionOperation <T>
{
public:
    QRootOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("root"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QRootOperation

template <class T>
class QLnOperation : public QUnarPrefixOperation <T>
{
public:
    QLnOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("ln"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QLnOperation

template <class T>
class QLbOperation : public QUnarPrefixOperation <T>
{
public:
    QLbOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("lb"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QLbOperation

template <class T>
class QLgOperation : public QUnarPrefixOperation <T>
{
public:
    QLgOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("lg"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QLgOperation

template <class T>
class QLogOperation : public QBinarFunctionOperation <T>
{
public:
    QLogOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("log"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QLogOperation

template <class T>
class QArcsinOperation : public QUnarPrefixOperation <T>
{
public:
    QArcsinOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("arcsin"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QArcsinOperation

template <class T>
class QArccosOperation : public QUnarPrefixOperation <T>
{
public:
    QArccosOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("arccos"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QArccosOperation

template <class T>
class QArctgOperation : public QUnarPrefixOperation <T>
{
public:
    QArctgOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("arctg"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QArctgOperation

template <class T>
class QArcctgOperation : public QUnarPrefixOperation <T>
{
public:
    QArcctgOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("arcctg"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QArcctgOperation

template <class T>
class QSecOperation : public QUnarPrefixOperation <T>
{
public:
    QSecOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("sec"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QSecOperation

template <class T>
class QCosecOperation : public QUnarPrefixOperation <T>
{
public:
    QCosecOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("cosec"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QCosecOperation

template <class T>
class QAbsOperation : public QUnarPrefixOperation <T>
{
public:
    QAbsOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("abs"); }
    QVector<QString> getDefaultSynonyms() const;
    int prepareQString(QString &str, QFunction<T> &parentFunction);
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QAbsOperation

template <class T>
class QNotOperation : public QUnarPrefixOperation <T>
{
public:
    QNotOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("not"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QNotOperation

template <class T>
class QLessOperation : public QBinarOperandOperation <T>
{
public:
    QLessOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("less"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QLessOperation

template <class T>
class QEqualOperation : public QBinarOperandOperation <T>
{
public:
    QEqualOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("equal"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QEqualOperation

template <class T>
class QNotequalOperation : public QBinarOperandOperation <T>
{
public:
    QNotequalOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("notequal"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QNotequalOperation

template <class T>
class QOverOperation : public QBinarOperandOperation <T>
{
public:
    QOverOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("over"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QOverOperation

template <class T>
class QNotoverOperation : public QBinarOperandOperation <T>
{
public:
    QNotoverOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("notover"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QNotoverOperation

template <class T>
class QNotlessOperation : public QBinarOperandOperation <T>
{
public:
    QNotlessOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("notless"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QNotlessOperation

template <class T>
class QOrOperation : public QBinarOperandOperation <T>
{
public:
    QOrOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("or"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QOrOperation

template <class T>
class QXorOperation : public QBinarOperandOperation <T>
{
public:
    QXorOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("xor"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QXorOperation

template <class T>
class QAndOperation : public QBinarOperandOperation <T>
{
public:
    QAndOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("and"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QAndOperation

template <class T>
class QBorOperation : public QBinarOperandOperation <T>
{
public:
    QBorOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("bor"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QBorOperation

template <class T>
class QBandOperation : public QBinarOperandOperation <T>
{
public:
    QBandOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("band"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QBandOperation

template <class T>
class QBnotOperation : public QUnarPrefixOperation <T>
{
public:
    QBnotOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("bnot"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QBnotOperation

template <class T>
class QBxorOperation : public QBinarOperandOperation <T>
{
public:
    QBxorOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("bxor"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QBxorOperation

template <class T>
class QBlshOperation : public QBinarOperandOperation <T>
{
public:
    QBlshOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("blsh"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QBlshOperation

template <class T>
class QBrshOperation : public QBinarOperandOperation <T>
{
public:
    QBrshOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("brsh"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QBlshOperation

template <class T>
class QSinhOperation : public QUnarPrefixOperation <T>
{
public:
    QSinhOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("sinh"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

private:

}; // End of QSinhOperation

template <class T>
class QCoshOperation : public QUnarPrefixOperation <T>
{
public:
    QCoshOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("cosh"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

private:

}; // End of QCoshOperation

template <class T>
class QTghOperation : public QUnarPrefixOperation <T>
{
public:
    QTghOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("tgh"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QTghOperation

template <class T>
class QCtghOperation : public QUnarPrefixOperation <T>
{
public:
    QCtghOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("ctgh"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QСtghOperation

template <class T>
class QSechOperation : public QUnarPrefixOperation <T>
{
public:
    QSechOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("sech"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QSechOperation

template <class T>
class QCosechOperation : public QUnarPrefixOperation <T>
{
public:
    QCosechOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("cosech"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QCosechOperation

template <class T>
class QAsinhOperation : public QUnarPrefixOperation <T>
{
public:
    QAsinhOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("asinh"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QAsinhOperation

template <class T>
class QAcoshOperation : public QUnarPrefixOperation <T>
{
public:
    QAcoshOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("acosh"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QAcoshOperation

template <class T>
class QAtghOperation : public QUnarPrefixOperation <T>
{
public:
    QAtghOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("atgh"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QAtghOperation

template <class T>
class QArctghOperation : public QUnarPrefixOperation <T>
{
public:
    QArctghOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("arctgh"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QArctghOperation

template <class T>
class QRoundOperation : public QUnarPrefixOperation <T>
{
public:
    QRoundOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("round"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QRoundOperation

template <class T>
class QTruncOperation : public QUnarPrefixOperation <T>
{
public:
    QTruncOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("trunc"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QTruncOperation

template <class T>
class QCeilOperation : public QUnarPrefixOperation <T>
{
public:
    QCeilOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("ceil"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QCeilOperation

template <class T>
class QFractOperation : public QUnarPrefixOperation <T>
{
public:
    QFractOperation(QOperation <T> *arg);
    T getResult() const;
    QString name() const {return QString("fract"); }
    QVector<QString> getDefaultSynonyms() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QFractOperation

template <class T>
class QModOperation : public QBinarOperandOperation <T>
{
public:
    QModOperation(QOperation <T> *arg1, QOperation <T> *arg2);
    T getResult() const;
    QString name() const {return QString("mod"); }
    QVector<QString> getDefaultSynonyms() const;
    int getDefaultPriority() const;
    QOperation <T> *getCopy(QFunction<T> *parentFunction) const;
    QOperation <T> *getDerivative(const QString &argName, QFunction<T> &parentFunction) const;

}; // End of QModOperation

template <class T>
class QFunction
{
    friend class QOperation<T>;

public:
    QFunction();
    ~QFunction();
    T result();
    int setString(const QString &str, const QOperationCompiler<T> &compiler =
            QOperationCompiler<T>::defaultCompiler);
    QFunctionVariable<T> *addVariable(const QString &name);
    QFunctionVariable<T> *getVariable(const QString &name);
    int setVariableValue(const QString &name, const T &value);
    QVector <QFunctionVariable <T> > *getVariableList();
    int getVariableNumber();
    QString toString(const QOperationCompiler<T> &compiler =
            QOperationCompiler<T>::defaultCompiler) const;
    QFunction <T> getDerivative(const QString &variableName,
                                uint optimizeFlags = OptimizeFlags::DEFAULT_OPTIMIZATION);
    void operator=(const QFunction &other);
    void getValueArray(QString arg1Name, QString arg2Name, T arg1Begin, T arg2Begin,
                       T arg1Step, T arg2Step, uint arg1Num, uint arg2Num) const;
    int draw(QPaintDevice *device, const QPoint &bottomLeft, int height,
             const QOperationCompiler<T> &compiler = QOperationCompiler<T>::defaultCompiler) const;
    QString getString() const {return _functionString; }

private:
    void connectVariableLinks();
    QOperation <T> *_operation;
    QString _functionString;
    QVector <QFunctionVariable <T> > _variables;

}; // End of QFunction

template <class T>
class QFunctionVariable
{
    friend class QVarOperation<T>;
    friend class QFunction <T>;

public:
    QFunctionVariable();
    QFunctionVariable(const QString &name); // Creates the variable with this name
    QFunctionVariable(const QString &name, const T &value);
    T *getValuePtr(); // Returns a pointer to the value of variable
    T getValue() const; // Returns the variable value
    void setValue(const T &value); // Sets the variable value
    const QString &getName() const; // Returns the variable name
    void setName(const QString &name); // Sets the variable name

private:
    QString _name;
    T _value;


}; // End of QFunctionVariable

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

// Functions
template <class T>
void clearQVector(QVector <T *> &vect)
{
    for (int i = 0; i < vect.length(); i++)
        delete vect[i];
    vect.clear();
}

template <class T>
void clearQStack(QStack <QStackUnit <T> > &stack)
{
    while (!stack.isEmpty())
        delete stack.pop().op;
}

inline bool doubleCmp(const double &d1, const double &d2)
{
    return fabs(d1 - d2) <= 1.0e-9 * (fmax(fabs(d1), fabs(d2)) + 1.0);
}
// end of Functions


// QOperation
template <class T>
QOperation<T>::~QOperation()
{
}

template <class T>
QOperation <T> *QOperation<T>::getOperationFromString(const QString &s, int &pos,
                                                      const QOperationCompiler <T> &compiler) const
{
    QVector<QString> synonyms = compiler.getContextMap()[name()].getSynonyms();
    for (int i = 0; i < synonyms.length(); i++) {
        bool contains = true;
        int j;
        for (j = 0; j < synonyms[i].length() && j + pos < s.length(); j++) {
            if (synonyms[i][j] != s[j + pos])
                contains = false;
        }

        if (pos + synonyms[i].length() > s.length())
            contains = false;

        if (contains) {
            if (pos + synonyms[i].length() < s.length() &&
                    compiler.getCompilationFlags() & CompilationFlags::STRICT_SYNTAX) {
                if (s[pos + synonyms[i].length()].isLetterOrNumber()) {
                    return nullptr;
                } else {
                    pos += synonyms[i].length();
                    return this->getCopy();
                }
            } else {
                pos += synonyms[i].length();
                return this->getCopy();
            }
        }
    }

    return nullptr;
}

template <class T>
QVector <QString> QOperation<T>::getDefaultSynonyms() const
{
    return QVector <QString>();
}

template <class T>
uint QOperation<T>::getDefaultAssociativity() const
{
    return QOperationAssociativity::leftToRight;
}

template <class T>
bool QOperation<T>::isOpeningBracket(const QChar &ch)
{
    if (ch == '(')
        return true;

    return false;
}

template <class T>
bool QOperation<T>::isClosingBracket(const QChar &ch)
{
    if (ch == ')')
        return true;

    return false;
}

template <class T>
int QOperation<T>::prepareQString(QString &, const QOperationCompiler<T> &) const
{
    return 0;
}

template <class T>
QOperation <T> *QOperation<T>::optimizeIfConstant(QFunction <T> &)
{
    return this;
}

template <class T>
QOperation <T> *QOperation<T>::optimizeSpecial(QFunction<T> &)
{
    return this;
}

template <class T>
void QOperation<T>::makeSumPolynomial(QVector<QOperation<T> *> &positive,
                                      QVector<QOperation<T> *> &)
{
    positive.push_back(this->getCopy());
}

template <class T>
QOperation <T> *QOperation<T>::optimizePolynomial(QFunction<T> &)
{
    return this;
}

template <class T>
QOperation <T> *QOperation<T>::optimize(QFunction <T> &function, uint flags)
{
    QOperation <T> *use = this;

    if (flags & OptimizeFlags::CONST_OPTIMIZATION)
        use = use->optimizeIfConstant(function);

    if (flags & OptimizeFlags::SPECIAL_OPTIMIZATION)
        use = use->optimizeSpecial(function);

    if (flags & OptimizeFlags::POLYNOMIAL_OPTIMIZATION)
        use = use->optimizePolynomial(function);

    return use;
}

template <class T>
bool QOperation<T>::isBinaryFunctionOperation() const
{
    return false;
}

template <class T>
QString QOperation<T>::name() const
{
    return "";
}

template <class T>
int QOperation<T>::getArgumentNum() const
{
    return 0;
}
// End of QOperation


// QOperationPtrVector
template <class T>
QOperationPtrVector<T>::QOperationPtrVector()
{
}

template <class T>
QOperationPtrVector<T>::~QOperationPtrVector()
{
    clear();
}

template <class T>
void QOperationPtrVector<T>::push_back(QOperation <T> *member)
{
    m_vector.push_back(member);
}

template <class T>
QOperationPtrVector<T> &QOperationPtrVector<T>::operator =(const QOperationPtrVector <T> &other)
{
    if (this != &other) {
        m_vector.clear();
        for (int i = 0; i < other.length(); i++)
            m_vector.push_back(other[i]->getCopy(nullptr));
    }

    return *this;
}

template <class T>
void QOperationPtrVector<T>::clear()
{
    for (int i = 0; i < m_vector.length(); i++)
        delete m_vector[i];
    m_vector.clear();
}
// End of QOperationPtrVector


// QOperationContext
QOperationContext::QOperationContext()
{
    m_priority = 0;
    m_associativity = QOperationAssociativity::leftToRight;
    m_synonyms = QVector<QString>();
    m_drawingName = QString("");
    m_drawingColor = Qt::black;
}

template <class T>
QOperationContext::QOperationContext(const QOperation<T> *operation)
{
    if (operation == nullptr) {
        m_priority = 0;
        m_associativity = QOperationAssociativity::leftToRight;
        m_synonyms = QVector<QString>();
        m_drawingName = QString("");
        m_drawingColor = Qt::black;
    } else {
        m_priority = operation->getDefaultPriority();
        m_associativity = operation->getDefaultAssociativity();
        m_synonyms = operation->getDefaultSynonyms();
        m_drawingName = m_synonyms.length() > 0 ? m_synonyms[0] : operation->name();
    }
}
// End of QOperationContext


// QOperationCompiler
template <class T>
QOperationCompiler<T>::QOperationCompiler() : m_compilationFlags(CompilationFlags::DEFAULT_COMPILATION_FLAGS),
    m_binaryOperationDelimeter(DEFAULT_BINARY_OPERATION_DELIMETER),
    m_convertionToStringFlags(OperationToStringConvertionFlags::DEFAULT_CONVERTION_FLAGS),
    m_drawingFlags(DrawingFlags::DEFAULT_DRAWING_FLAGS),
    m_doubleDrawingBase(10),
    m_doublePrecision(8),
    m_drawingUnarSpaceWidth(0.7),
    m_drawingBinarSpaceWidth(0.7)
{
    initOperationList();
    initDefaultContext();
    m_openingBracket = QChar('(');
    m_closingBracket = QChar(')');
    m_spaceChar      = QChar(' ');
}

template <class T>
QOperationCompiler<T>::QOperationCompiler(uint compilationFlags, uint optimizationFlags,
                                          uint convertionToStringFlags) :
    m_compilationFlags(compilationFlags),
    m_binaryOperationDelimeter(optimizationFlags),
    m_convertionToStringFlags(convertionToStringFlags),
    m_drawingFlags(DrawingFlags::DEFAULT_DRAWING_FLAGS),
    m_doubleDrawingBase(10),
    m_doublePrecision(8),
    m_drawingUnarSpaceWidth(0.7),
    m_drawingBinarSpaceWidth(0.7)
{
    initOperationList();
    initDefaultContext();
    m_openingBracket = QChar('(');
    m_closingBracket = QChar(')');
    m_spaceChar      = QChar(' ');
}

template <class T>
QOperationCompiler<T>::~QOperationCompiler()
{
    m_operations.clear();
}

template <class T>
uint QOperationCompiler<T>::getDefaultCompilationFlags() const
{
    return CompilationFlags::DEFAULT_COMPILATION_FLAGS;
}

template <>
uint QOperationCompiler<double>::getDefaultCompilationFlags() const
{
    return CompilationFlags::DEFAULT_DOUBLE_COMPILATION_FLAGS;
}

template <class T>
uint QOperationCompiler<T>::getOptimizationFlags() const
{
    return m_optimizationFlags;
}

template <class T>
int QOperationCompiler<T>::initContextFromFile(QString path)
{
    typedef int default_type;
    QString literalConstPrefix = QString("constant:");
    QString priorityPostfix = QString("_p:");
    QString synonymsPostfix = QString("_s:");
    QString associativityPostfix = QString("_a:");
    QString rightToLeftAssociativityString = QString("right_to_left");
    QString drawingNamePostfix = QString("_d:");
    QString drawingColorPostfix = QString("_c:");

    QFile synonymsFile(path);
    if (!synonymsFile.exists())
        return -1;

    if (!synonymsFile.open(QIODevice::ReadOnly))
        return -1;

    QByteArray byteArray = synonymsFile.readLine();
    while (!byteArray.isEmpty()) {
        QVector <QString> synonyms;
        QString s(byteArray);
        s.remove("\n");
        s.remove("\r");
        QStringList sl = s.split(" ");
        if (sl.isEmpty())
            continue;

        if (!sl[0].startsWith(literalConstPrefix)) {
            if (sl.length() < 2) {
                byteArray = synonymsFile.readLine();
                continue;
            }
            for (int i = 0; i < getAllOperationList().length(); i++) {
                if (sl[0].startsWith(getAllOperationList()[i]->name() + synonymsPostfix)) {
                    for (int j = 1; j < sl.length(); j++)
                        synonyms.push_back(sl[j]);

                    m_operationContextMap[getAllOperationList()[i]->name()].setSynonyms(synonyms);
                    break;
                } else if (sl[0].startsWith(getAllOperationList()[i]->name() + priorityPostfix)) {
                    m_operationContextMap[getAllOperationList()[i]->name()].setPriority(sl[1].
                            toInt());
                    break;
                } else if (sl[0].startsWith(getAllOperationList()[i]->name() +
                                            associativityPostfix)) {
                    m_operationContextMap[getAllOperationList()[i]->name()].setAssociativity(
                                sl[1] == rightToLeftAssociativityString ? QOperationAssociativity::
                                                                          rightToLeft :
                                                                          QOperationAssociativity::
                                                                          leftToRight);
                    break;
                } else if (sl[0].startsWith(getAllOperationList()[i]->name() + drawingNamePostfix)){
                    m_operationContextMap[getAllOperationList()[i]->name()].setDrawingName(sl[1]);
                    break;
                } else if (sl[0].startsWith(getAllOperationList()[i]->name() +
                                            drawingColorPostfix)) {
                    bool ok;
                    QColor color(sl[1].toInt(&ok, 16));
                    m_operationContextMap[getAllOperationList()[i]->name()].setDrawingColor(
                                color);
                    break;
                }
            }
        } else {
            QString name;
            T value = T();
            QConstOperation<T> constOp;
            QOperation<T> *op = nullptr;
            if (sl.length() > 0)
                name = sl[1];
            if (sl.length() > 1) {
                int k = 0;
                op = constOp.getOperationFromString(sl[2], k, *this);
            }
            if (op != nullptr) {
                value = op->getResult();
                delete op;
            }
            m_literalConstants.push_back(QFunctionVariable<T>(name, value));
        }
        byteArray = synonymsFile.readLine();
    }

    return 0;
}

template <class T>
QOperation <T> *QOperationCompiler<T>::compile(QString &functionString,
                                               QFunction <T> &parentFunction, int &errorPos) const
{
    QStack <QStackUnit <T> > stack1;
    QStack <QStackUnit <T> > stack2;
    QStack <QStackUnit <T> > stack3;
    QStackUnit <T> unit;
    bool needPop;
    int brackets = 0, brackets1;
    int pos = 0;

    while (pos < functionString.length()) {
        if (isOpeningBracket(functionString[pos])) {
            brackets++;
            pos++;
            continue;
        }
        if (isClosingBracket(functionString[pos])) {
            brackets--;
            pos++;
            continue;
        }
        if (functionString[pos] == QChar(' ')) {
            pos++;
            continue;
        }
        if (brackets < 0) { // When smth went wrong
            if (&errorPos != nullptr)
                errorPos = pos + 1;
            clearQStack(stack1);
            clearQStack(stack2);
            return nullptr;
        }
        QOperation <T> *operation;
        if (functionString[pos] == m_binaryOperationDelimeter) {
            if (stack3.isEmpty()) {
                if (&errorPos != nullptr)
                    errorPos = pos;
                clearQStack(stack1);
                clearQStack(stack2);
                return nullptr;
            }
            pos++;
            unit = stack3.pop();
            operation = unit.op;
            brackets1 = unit.brackets;
        } else {
            operation = getOperationFromString(functionString, pos);
            if (operation == nullptr) { // Smth went wrong
                if (&errorPos != nullptr)
                    errorPos = pos + 1;
                clearQStack(stack1);
                clearQStack(stack2);
                return nullptr;
            }
            if (operation->isBinaryFunctionOperation()) {
                unit.op = operation;
                unit.brackets = brackets;
                stack3.push(unit);
                continue;
            }
            brackets1 = brackets;
        }

        if (operation == nullptr) {
            pos++;
        } else {
            if (operation->getDefaultPriority() >= CONST_OPERATION_PRIORITY) {
                unit.op = operation; // Brackets don`t matter
                stack2.push(unit);
            } else {
                if (stack1.isEmpty())
                    needPop = false;
                else {
                    if (stack1.top().brackets > brackets1) {
                        needPop = true;
                    } else if (stack1.top().brackets == brackets1){
                        if (stack1.top().op->getDefaultPriority() >
                                operation->getDefaultPriority())
                            needPop = true;
                        else if (stack1.top().op->getDefaultPriority() <
                                 operation->getDefaultPriority())
                            needPop = false;
                        else if (operation->getDefaultAssociativity() ==
                                 QOperationAssociativity::leftToRight)
                            needPop = true;
                        else
                            needPop = false;
                    } else
                        needPop = false;
                }
                while (needPop) {
                    QOperation <T> *use = stack1.pop().op;
                    if (use->compileFromStack(stack2) != 0) { // When smth went wrong
                        if (&errorPos != nullptr)
                            errorPos = pos + 1;
                        delete use;
                        clearQStack(stack1);
                        clearQStack(stack2);
                        return nullptr;
                    }
                    unit.op = use;
                    unit.brackets = brackets;
                    stack2.push(unit);
                    if (stack1.isEmpty())
                        needPop = false;
                    else {
                        if (stack1.top().brackets > brackets1) {
                            needPop = true;
                        } else if (stack1.top().brackets == brackets1){
                            if (stack1.top().op->getDefaultPriority() >
                                    operation->getDefaultPriority())
                                needPop = true;
                            else if (stack1.top().op->getDefaultPriority() <
                                     operation->getDefaultPriority())
                                needPop = false;
                            else if (operation->getDefaultAssociativity() ==
                                     QOperationAssociativity::leftToRight)
                                needPop = true;
                            else
                                needPop = false;
                        } else
                            needPop = false;
                    }
                }
                unit.op = operation;
                unit.brackets = brackets1;
                stack1.push(unit);
            }
        }
    }

    if (brackets != 0) { // When smth went wrong
        if (&errorPos != nullptr)
            errorPos = -1;
        clearQStack(stack1);
        clearQStack(stack2);
        return nullptr;
    }

    while (!stack1.isEmpty()) {
        QOperation <T> *use = stack1.pop().op;
        if (use->compileFromStack(stack2) != 0) { // When smth went wrong
            if (&errorPos != nullptr)
                errorPos = -1;
            delete use;
            clearQStack(stack1);
            clearQStack(stack2);
            return nullptr;
        }
        unit.op = use;
        stack2.push_back(unit);
    }

    if (stack2.isEmpty()) { // When smth went wrong
        if (&errorPos != nullptr)
            errorPos = -1;
        clearQStack(stack1);
        clearQStack(stack2);
        return nullptr;
    }

    QOperation <T> *result = stack2.pop().op;
    if (!stack2.isEmpty()) { // When smth went wrong
        if (&errorPos != nullptr)
            errorPos = -1;
        delete result;
        clearQStack(stack1);
        clearQStack(stack2);
        return nullptr;
    }
    errorPos = 0;

    result->addVariablesToList(parentFunction);
    for (int j = 0; j < parentFunction.getVariableNumber(); j++)
        result->connectVarLinks(&(*parentFunction.getVariableList())[j]);

    return result;
}

template <class T>
int QOperationCompiler<T>::prepareString(QString &s) const
{
    int err = 0;
    for (int i = 0; i < m_operations.length(); i++)
        if ((err = m_operations[i]->prepareQString(s, *this)) != 0)
            return err;

    return 0;
}

template <class T>
bool QOperationCompiler<T>::isOpeningBracket(QChar ch) const
{
    QChar openingSquareBracket('[');
    QChar openingCurlyBracket('{');
    QChar openingRoundBracket('(');
    if ((m_compilationFlags & CompilationFlags::ALLOW_CURLY_BRACKETS) && ch == openingCurlyBracket)
        return true;
    if ((m_compilationFlags & CompilationFlags::ALLOW_SQARE_BRACKETS) && ch == openingSquareBracket)
        return true;
    if ((m_compilationFlags & CompilationFlags::ALLOW_ROUND_BRACKETS) && ch == openingRoundBracket)
        return true;

    return false;
}

template <class T>
bool QOperationCompiler<T>::isClosingBracket(QChar ch) const
{
    QChar closingSquareBracket(']');
    QChar closingCurlyBracket('}');
    QChar closingRoundBracket(')');
    if ((m_compilationFlags & CompilationFlags::ALLOW_CURLY_BRACKETS) && ch == closingCurlyBracket)
        return true;
    if ((m_compilationFlags & CompilationFlags::ALLOW_SQARE_BRACKETS) && ch == closingSquareBracket)
        return true;
    if ((m_compilationFlags & CompilationFlags::ALLOW_ROUND_BRACKETS) && ch == closingRoundBracket)
        return true;

    return false;
}

template <class T>
const QOperationPtrVector <T> &QOperationCompiler<T>::getAllOperationList() const
{
    return m_operations;
}

template <class T>
int QOperationCompiler<T>::getOperationNumber() const
{
    QOperationPtrVector <int> vect;
    return vect.length();
}

template <class T>
QOperation <T> *QOperationCompiler<T>::getOperationFromString(const QString &s, int &pos) const
{
    QOperation<T> *newOp = nullptr;
    for (int i = 0; i < m_operations.length(); i++) {
        if ((newOp = m_operations[i]->getOperationFromString(s, pos, *this)) != nullptr)
            break;
    }

    return newOp;
}

template <class T>
void QOperationCompiler<T>::setCompilationFlags(uint flags)
{
    m_compilationFlags = flags;
}

template <class T>
void QOperationCompiler<T>::setConvertionToStringFlags(uint flags)
{
    m_convertionToStringFlags = flags;
}

template <class T>
void QOperationCompiler<T>::setOptimizationFlags(uint flags)
{
    m_optimizationFlags = flags;
}

template <class T>
uint QOperationCompiler<T>::getDrawingFlags() const
{
    return m_drawingFlags;
}

template <class T>
uint QOperationCompiler<T>::getConvetionToStringFlags() const
{
    return m_convertionToStringFlags;
}

template <class T>
int QOperationCompiler<T>::getOperationPriority(const QOperation<T> *operation) const
{
    return m_operationContextMap[operation->name()].getPriority();
}

template <class T>
uint QOperationCompiler<T>::getOperationAssociativity(const QOperation <T> *operation) const
{
    return m_operationContextMap[operation->name()].getAssociativity();
}

template <class T>
const QString &QOperationCompiler<T>::getOperationMainSynonym(const QOperation <T> *operation) const
{
    return m_operationContextMap[operation->name()].getSynonyms()[0];
}

template <class T>
T QOperationCompiler<T>::getValueFromString(const QString &s, int &pos, int &ok) const
{
    if (!s[pos].isDigit() && s[pos] != QChar('-')) {
        ok = -1;
        return 0.0;
    }
    if (pos > 0 && s[pos - 1].isLetterOrNumber()) {
        ok = -1;
        return 0.0;
    }
    if (pos + 1 < s.length() && s[pos] == QChar('-') && !s[pos + 1].isDigit()) {
        ok = -1;
        return 0.0;
    }
    if (pos == s.length() - 1 && s[pos] == QChar('-')) {
        ok = -1;
        return 0.0;
    }
    if (s[pos] == QChar('-') && (pos != 0 || isOpeningBracket(s[pos - 1]))) {
        ok = -1;
        return 0.0;
    }
    int charNumber = pos;
    QString use;
    double d = 0.0, t;
    QChar char_mod[] = {'b', 'h', 'x'};
    int   base_mod[] = {  2,   8,  16};
    if (s[charNumber] == '-') {
        use += s[charNumber];
        charNumber++;
    }

    if (s[charNumber] == '0') {
        if (charNumber == s.length() - 1) {
            pos++;
            return 0.0;
        }
        for (unsigned int charModNumber = 0; charModNumber < sizeof(char_mod) / sizeof(QChar);
             charModNumber++) {
            if (s[charNumber + 1] == char_mod[charModNumber]) {
                charNumber += 2;
                while (charNumber < s.length() && s[charNumber].isLetterOrNumber()) {
                    d = d * base_mod[charModNumber] + ('F' >= s[charNumber].toLatin1() &&
                                                       s[charNumber].toLatin1() >= 'A' ?
                                               s[charNumber].toLatin1() - 'A' + 10 :
                                               ('f' >= s[charNumber].toLatin1() &&
                                                s[charNumber].toLatin1() >= 'a' ?
                                                    s[charNumber].toLatin1() - 'a' + 10 :
                                                    s[charNumber].toLatin1() - '0'));
                    charNumber++;
                }
                if (charNumber >= s.length() || (charNumber < s.length() &&
                                        s[charNumber].toLatin1() !=
                                                 QOperation<double>::FLOATING_POINT)) {
                    pos = charNumber;
                    return d;
                }
                charNumber++;
                t = (double) 1 / base_mod[charModNumber];
                while (charNumber < s.length() && s[charNumber].isLetterOrNumber()) {
                    d += t * ('F' >= s[charNumber].toLatin1() && s[charNumber].toLatin1() >= 'A' ?
                                  s[charNumber].toLatin1() - 'A' + 10 :
                                  ('f' >= s[charNumber].toLatin1() && s[charNumber].toLatin1() >=
                                   'a' ?
                                       s[charNumber].toLatin1() - 'a' + 10 :
                                       s[charNumber].toLatin1() - '0'));
                    t /= base_mod[charModNumber];
                    charNumber++;
                }
                pos = charNumber;
                return d;
            }
        }
        while (charNumber < s.length() && s[charNumber].isDigit()) {
            use += s[charNumber];
            charNumber++;
        }
        if (charNumber < s.length() && s[charNumber] == QOperation<double>::FLOATING_POINT) {
            use += s[charNumber];
            charNumber++;
        }
        while (charNumber < s.length() && s[charNumber].isDigit()) {
            use += s[charNumber];
            charNumber++;
        }
        pos = charNumber;
        return use.toDouble();
    } else {
        while (charNumber < s.length() && (s[charNumber].isDigit() ||
                                  s[charNumber].toLatin1() == QOperation<double>::FLOATING_POINT)) {
            use += s[charNumber];
            charNumber++;
        }
        pos = charNumber;
        return use.toDouble();
    }

    ok = -1;
    return 0.0;
}

template <class T>
bool QOperationCompiler<T>::isVariableSymbol(QChar ch) const
{
    if (ch.isLetterOrNumber())
        return true;
    if (ch == QChar('_'))
        return true;
    if (ch == QChar('\''))
        return true;
    if (QChar('а') <= ch && ch <= QChar('я'))
        return true;

    return false;
}

template <class T>
bool QOperationCompiler<T>::isFirstVariableSymbol(QChar ch) const
{
    if (ch.isLetter())
        return true;
    if (QChar('а') <= ch && ch <= QChar('я'))
        return true;

    return false;
}

template <class T>
const QString &QOperationCompiler<T>::getOperationDrawingName(const QOperation<T> *op) const
{
    return m_operationContextMap[op->name()].getDrawingName();
}

template <class T>
const QColor &QOperationCompiler<T>::getOperationDrawingColor(const QOperation<T> *op) const
{
    return m_operationContextMap[op->name()].getDrawingColor();
}

template <class T>
void QOperationCompiler<T>::initOperationList()
{
    m_operations.clear();

    if (m_compilationFlags & CompilationFlags::ALLOW_CONSTANTS) {
        m_operations.push_back(new QConstOperation<T>(0)); // Must be the first
    }
    if (m_compilationFlags & CompilationFlags::ALLOW_COMMON_OPERATIONS) {
        m_operations.push_back(new QNegOperation<T>(nullptr)); // Must be before sub
        m_operations.push_back(new QSumOperation<T>(nullptr, nullptr));
        m_operations.push_back(new QSubOperation<T>(nullptr, nullptr)); // Must be after neg
        m_operations.push_back(new QMulOperation<T>(nullptr, nullptr));
        m_operations.push_back(new QDivOperation<T>(nullptr, nullptr));
    }
    if (m_compilationFlags & CompilationFlags::ALLOW_SIGN_OPERATIONS) {
        m_operations.push_back(new QSignOperation<T>(nullptr));
        m_operations.push_back(new QAbsOperation<T>(nullptr));
    }
    if (m_compilationFlags & CompilationFlags::ALLOW_BIT_OPERATIONS) {
        m_operations.push_back(new QBxorOperation<T>(nullptr, nullptr)); // Must be before pow = "^"
        m_operations.push_back(new QBlshOperation<T>(nullptr, nullptr)); // Must be before logic operations
        m_operations.push_back(new QBrshOperation<T>(nullptr, nullptr)); // Must be before logic operations
        m_operations.push_back(new QBorOperation<T>(nullptr, nullptr)); // Must be before logic "or" = "|"
        m_operations.push_back(new QBandOperation<T>(nullptr, nullptr)); // Must be before logic "and" = "&"
        m_operations.push_back(new QBnotOperation<T>(nullptr));
    }
    if (m_compilationFlags & CompilationFlags::ALLOW_POWER_OPERATIONS) {
        m_operations.push_back(new QExpOperation<T>(nullptr));
        m_operations.push_back(new QSqrtOperation<T>(nullptr));
        m_operations.push_back(new QRootOperation<T>(nullptr, nullptr));
        m_operations.push_back(new QPowOperation<T>(nullptr, nullptr)); // Must be after bit "xor" = "^^"
    }
    if (m_compilationFlags & CompilationFlags::ALLOW_LOGARITHM_OPERATIONS) {
        m_operations.push_back(new QLnOperation<T>(nullptr));
        m_operations.push_back(new QLgOperation<T>(nullptr));
        m_operations.push_back(new QLbOperation<T>(nullptr));
        m_operations.push_back(new QLogOperation<T>(nullptr, nullptr));
    }
    if (m_compilationFlags & CompilationFlags::ALLOW_LOGIC_OPERATIONS) {
        m_operations.push_back(new QNotoverOperation<T>(nullptr, nullptr)); // Must be before less operation
        m_operations.push_back(new QNotlessOperation<T>(nullptr, nullptr)); // Must be before over operation
        m_operations.push_back(new QNotequalOperation<T>(nullptr, nullptr)); // Must be before equal operation
        m_operations.push_back(new QNotOperation<T>(nullptr)); // Must be after equal operation "!="
        m_operations.push_back(new QLessOperation<T>(nullptr, nullptr));
        m_operations.push_back(new QOverOperation<T>(nullptr, nullptr));
        m_operations.push_back(new QEqualOperation<T>(nullptr, nullptr));
        m_operations.push_back(new QOrOperation<T>(nullptr, nullptr)); // Must be after bit "or" = "||"
        m_operations.push_back(new QAndOperation<T>(nullptr, nullptr)); // Must be agter bit "and" = "&&"
        m_operations.push_back(new QXorOperation<T>(nullptr, nullptr));
    }
    if (m_compilationFlags & CompilationFlags::ALLOW_HYPERBOLIC_OPERATIONS) {
        m_operations.push_back(new QSinhOperation<T>(nullptr)); // Must be after bit shifts, before sin
        m_operations.push_back(new QCoshOperation<T>(nullptr)); // Must be after bit shifts, before cos
        m_operations.push_back(new QTghOperation<T>(nullptr)); // Must be before tangent
        m_operations.push_back(new QCtghOperation<T>(nullptr)); // Must be before cotangent
        m_operations.push_back(new QSechOperation<T>(nullptr)); // Must be before secant
        m_operations.push_back(new QCosechOperation<T>(nullptr)); // Must be before cosecant
        m_operations.push_back(new QAsinhOperation<T>(nullptr)); // Must be before arcsine
        m_operations.push_back(new QAcoshOperation<T>(nullptr)); // Must be before arccosine
        m_operations.push_back(new QAtghOperation<T>(nullptr)); // Must be before arctangent
        m_operations.push_back(new QArctghOperation<T>(nullptr)); // Must be before arccotangent
    }
    if (m_compilationFlags & CompilationFlags::ALLOW_TRIGONOMETRIC_OPERATIONS) {
        m_operations.push_back(new QSinOperation<T>(nullptr)); // Must be after sinh
        m_operations.push_back(new QCosOperation<T>(nullptr)); // Must be after cosh
        m_operations.push_back(new QTgOperation<T>(nullptr)); // Must be after tanh
        m_operations.push_back(new QCtgOperation<T>(nullptr)); // Must be after coth
        m_operations.push_back(new QSecOperation<T>(nullptr)); // Must be afte hyperbolic secant
        m_operations.push_back(new QCosecOperation<T>(nullptr)); // Must be after hyperbolic cosecant
        m_operations.push_back(new QArcsinOperation<T>(nullptr)); // Must be after hyperbolic arcsine
        m_operations.push_back(new QArccosOperation<T>(nullptr)); // Must be after hyperbolic arccosine
        m_operations.push_back(new QArctgOperation<T>(nullptr)); // Must be after hyperbolic arctangent
        m_operations.push_back(new QArcctgOperation<T>(nullptr)); // Must be after hyperbolic arccotangent
    }
    if (m_compilationFlags & CompilationFlags::ALLOW_INTEGER_OPERATIONS) {
        m_operations.push_back(new QModOperation<T>(nullptr, nullptr));
    }
    if (m_compilationFlags & CompilationFlags::ALLOW_FLOAT_OPERATIONS) {
        m_operations.push_back(new QRoundOperation<T>(nullptr));
        m_operations.push_back(new QTruncOperation<T>(nullptr));
        m_operations.push_back(new QCeilOperation<T>(nullptr));
        m_operations.push_back(new QFractOperation<T>(nullptr));
    }

    if (m_compilationFlags & CompilationFlags::ALLOW_VARIABLES) {
        m_operations.push_back(new QVarOperation<T>(nullptr)); // Must be the last
    }

    return;
}

template <class T>
void QOperationCompiler<T>::initDefaultContext()
{
    for (int i = 0; i < m_operations.length(); i++) {
        QOperationContext context(m_operations[i]);
        m_operationContextMap[m_operations[i]->name()] = context;
    }
}

template <>
const QOperationCompiler<double> QOperationCompiler<double>::defaultCompiler(
        CompilationFlags::DEFAULT_DOUBLE_COMPILATION_FLAGS,
        OptimizeFlags::DEFAULT_OPTIMIZATION,
        OperationToStringConvertionFlags::DEFAULT_CONVERTION_FLAGS);

template <class T>
const QOperationCompiler<T> QOperationCompiler<T>::defaultCompiler(
        CompilationFlags::DEFAULT_COMPILATION_FLAGS,
        OptimizeFlags::DEFAULT_OPTIMIZATION,
        OperationToStringConvertionFlags::DEFAULT_CONVERTION_FLAGS);
// End of QOperationCompiler


// QFunctionVariable
template <class T>
QFunctionVariable<T>::QFunctionVariable()
{
    _name = "";
}

template <class T>
QFunctionVariable<T>::QFunctionVariable(const QString &name)
{
    _name = name;
}

template <class T>
QFunctionVariable<T>::QFunctionVariable(const QString &name, const T &value)
{
    _name = name;
    _value = value;
}

template <class T>
T *QFunctionVariable<T>::getValuePtr()
{
    return &_value;
}

template <class T>
T QFunctionVariable<T>::getValue() const
{
    return _value;
}

template <class T>
void QFunctionVariable<T>::setName(const QString &name)
{
    _name = name;
}

template <class T>
void QFunctionVariable<T>::setValue(const T &value)
{
    _value = value;
}

template <class T>
const QString &QFunctionVariable<T>::getName() const
{
    return _name;
}
// End of QFunctionVariable


// QFunction
template <class T>
QFunction<T>::QFunction()
{
    _operation = nullptr;
}

template <class T>
QFunction<T>::~QFunction()
{
    if (_operation != nullptr)
        delete _operation;
}

template <class T>
T QFunction<T>::result()
{
    if (_operation != nullptr)
        return _operation->getResult();
    return 0.0;
}

template <class T>
int QFunction<T>::setString(const QString &s, const QOperationCompiler<T> &compiler)
{
     if (_operation != nullptr) {
        delete _operation;
        _operation = nullptr;
    }
    QVector<QFunctionVariable<T> > oldVariables = _variables;
    _variables.clear();

    _functionString = s;

    if (_functionString.isEmpty())
        return -1;

    compiler.prepareString(_functionString);

    int errorPos = 0;
    _operation = compiler.compile(_functionString, *this, errorPos);
    if (errorPos != 0)
        return errorPos;

    _operation = _operation->optimize(*this, compiler.getOptimizationFlags());
    for (int i = 0; i < _variables.length(); i++) {
        _variables[i].setValue(0.0);
        for (int j = 0; j < compiler.getLiteralConstants().length(); j++)
            if (_variables[i].getName() == compiler.getLiteralConstants()[j].getName())
                _variables[i].setValue(compiler.getLiteralConstants()[j].getValue());
        for (int j = 0; j < oldVariables.length(); j++)
            if (oldVariables[j].getName() == _variables[i].getName())
                _variables[i].setValue(oldVariables[j].getValue());
    }

    return errorPos;
}

template <class T>
QFunctionVariable <T> *QFunction<T>::addVariable(const QString &name)
{
    for (int i = 0; i < _variables.length(); i++)
        if (_variables[i].getName() == name)
            return &(_variables[i]);
    QFunctionVariable <T> var;
    var.setName(name);
    _variables.push_back(var);
    return &_variables[_variables.length() - 1];
}

template <class T>
QFunctionVariable <T> *QFunction<T>::getVariable(const QString &name)
{
    for (int i = 0; i < _variables.length(); i++)
        if (_variables[i]._name == name)
            return &_variables[i];
    return nullptr;
}

template <class T>
int QFunction<T>::setVariableValue(const QString &name, const T &value)
{
    for (int i = 0; i < _variables.length(); i++)
        if (_variables[i]._name == name) {
            _variables[i].setValue(value);
            return 0;
        }
    return -1;
}

template <class T>
QVector <QFunctionVariable <T> > *QFunction<T>::getVariableList()
{
    return &_variables;
}

template <class T>
int QFunction<T>::getVariableNumber()
{
    return _variables.length();
}

template <class T>
QString QFunction<T>::toString(const QOperationCompiler<T> &compiler) const
{
    if (_operation == nullptr)
        return QString("");
    else
        return _operation->toQString(compiler);
}

template <class T>
QFunction <T> QFunction<T>::getDerivative(const QString &arg, uint flags)
{
    QFunction <T> func;
    if (_operation == nullptr)
        return func;
    func._operation = _operation->getDerivative(arg, func);
    func.connectVariableLinks();
    func._operation = func._operation->optimize(func, flags);

    return func;
}

template <class T>
void QFunction<T>::connectVariableLinks()
{
    if (_operation == nullptr)
        return;
    for (int i = 0; i < _variables.length(); i++)
        _operation->connectVarLinks(&_variables[i]);
}

template <class T>
void QFunction<T>::operator =(const QFunction &other)
{
    if (_operation != nullptr)
        delete _operation;
    _variables.clear();
    if (other._operation != nullptr)
        _operation = other._operation->getCopy(*this);
    else
        _operation = nullptr;
    connectVariableLinks();
}

template <class T>
void QFunction<T>::getValueArray(QString arg1Name, QString arg2Name, T arg1Begin, T arg2Begin,
                   T arg1Step, T arg2Step, uint arg1Num, uint arg2Num) const
{
    QVector <T> constants;
    QVector <uint> funcNumber;
    QVector <T *> arg1;
    QVector <T *> arg2;
    QVector <T *> result;


}

template <class T>
int QFunction<T>::draw(QPaintDevice *device, const QPoint &bottomLeft, int height,
                       const QOperationCompiler<T> &compiler) const
{
    if (_operation != nullptr)
        _operation->draw(device, compiler, bottomLeft, height, false);
}
// End of QFunction


// Beginning of QBinarOperation's methods' description
template <class T>
QBinarOperation<T>::QBinarOperation(QOperation<T> *arg1, QOperation<T> *arg2)
{
    _arg1 = (QOperation<T> *) arg1;
    _arg2 = (QOperation<T> *) arg2;
}

template <class T>
QBinarOperation<T>::~QBinarOperation()
{
    delete this->_arg1;
    delete this->_arg2;
}

template <class T>
int QBinarOperation<T>::compileFromStack(QStack<QStackUnit <T> > &stack)
{
    if (stack.isEmpty())
        return -1;

    this->_arg2 = stack.pop().op;

    if (stack.isEmpty())
        return -1;

    this->_arg1 = stack.pop().op;

    return 0;
}

template <class T>
void QBinarOperation<T>::addVariablesToList(QFunction<T> &func)
{
    this->_arg1->addVariablesToList(func);
    this->_arg2->addVariablesToList(func);
}

template <class T>
void QBinarOperation<T>::connectVarLinks(QFunctionVariable<T> *var)
{
    this->_arg1->connectVarLinks(var);
    this->_arg2->connectVarLinks(var);
}

template <class T>
bool QBinarOperation<T>::isAlwaysConstant() const
{
    return this->_arg1->isAlwaysConstant() && this->_arg2->isAlwaysConstant();
}

template <class T>
QOperation<T> *QBinarOperation<T>::getCopy() const
{
    QBinarOperation<T> *ptr = (QBinarOperation<T> *)malloc(sizeof(*this));
    byteCopy((void *)this, (void *)ptr, sizeof(*this));
    ptr->_arg1 = this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy();
    ptr->_arg2 = this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy();
    return ptr;
}

template <class T>
QOperation <T> *QBinarOperation<T>::optimizeIfConstant(QFunction <T> &func)
{
    if (this->_arg1->isAlwaysConstant() && this->_arg2->isAlwaysConstant()) {
        T use = this->getResult();
        delete this;
        return new QConstOperation<T>(use);
    } else {
        this->_arg1 = this->_arg1->optimizeIfConstant(func);
        this->_arg2 = this->_arg2->optimizeIfConstant(func);
    }
    return this;
}

template <class T>
QOperation <T> *QBinarOperation<T>::optimizeSpecial(QFunction<T> &function)
{
    this->_arg1 = this->_arg1->optimizeSpecial(function);
    this->_arg2 = this->_arg2->optimizeSpecial(function);

    return this;
}

template <class T>
QOperation <T> *QBinarOperation<T>::optimizePolynomial(QFunction<T> &func)
{
    this->_arg1 = this->_arg1->optimizePolynomial(func);
    this->_arg2 = this->_arg2->optimizePolynomial(func);

    return this;
}
// End of QBinarOperation's methods' description


// Beginning of QBinarOperandOperation's methods' description
template <class T>
QBinarOperandOperation<T>::QBinarOperandOperation(QOperation<T> *arg1, QOperation<T> *arg2):
        QBinarOperation<T>(arg1, arg2)
{

}

template <class T>
QString QBinarOperandOperation<T>::toQString(const QOperationCompiler<T> &compiler) const
{
    QString s1, s2;
    if (this->_arg1->getDefaultPriority() < this->getDefaultPriority())
        s1 = this->OPENING_BRACKET + this->_arg1->toQString(compiler) + this->CLOSING_BRACKET;
    else if (this->_arg1->getDefaultPriority() == this->getDefaultPriority() &&
             this->getDefaultAssociativity() == QOperationAssociativity::rightToLeft)
        s1 = this->OPENING_BRACKET + this->_arg1->toQString(compiler) + this->CLOSING_BRACKET;
    else
        s1 = this->_arg1->toQString(compiler);

    if (this->_arg2->getDefaultPriority() < this->getDefaultPriority())
        s2 = this->OPENING_BRACKET + this->_arg2->toQString(compiler) + this->CLOSING_BRACKET;
    else if (this->_arg2->getDefaultPriority() == this->getDefaultPriority() &&
             this->getDefaultAssociativity() == QOperationAssociativity::leftToRight)
        s2 = this->OPENING_BRACKET + this->_arg2->toQString(compiler) + this->CLOSING_BRACKET;
    else
        s2 = this->_arg2->toQString(compiler);

    return s1 + " " + this->getDefaultSynonyms()[0] + " " + s2;
}

template <class T>
int QBinarOperandOperation<T>::getDefaultPriority() const
{
    return 5;
}

template <class T>
int QBinarOperandOperation<T>::draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                                    const QPoint &bottomLeft, int height, bool inBrackets) const
{
    return drawString(device, compiler, bottomLeft, height, inBrackets);
}

template <class T>
int QBinarOperandOperation<T>::getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                               bool inBrackets) const
{
    return getDrawnStringWidth(compiler, height, inBrackets);
}

template <class T>
int QBinarOperandOperation<T>::drawString(QPaintDevice *device,
                                          const QOperationCompiler<T> &compiler,
                                        const QPoint &bottomLeft, int height, bool inBrackets) const
{
    QPoint currentPos = bottomLeft;
    double spaceWidth = compiler.getDrawingBinarSpaceWidth();
    bool arg1IsInBrackets = compiler.getOperationPriority(this) >
            compiler.getOperationPriority(this->_arg1) || (compiler.getOperationPriority(this) ==
            compiler.getOperationPriority(this->_arg1) && compiler.getOperationAssociativity(
                                                               this->_arg1) ==
                                                          QOperationAssociativity::rightToLeft);
    bool arg2IsInBrackets = (compiler.getOperationPriority(this) >
            compiler.getOperationPriority(this->_arg2)) || ((compiler.getOperationPriority(this) ==
            compiler.getOperationPriority(this->_arg2)) && (compiler.getOperationAssociativity(
                                                                this->_arg2) ==
                                                          QOperationAssociativity::leftToRight));
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    QPen pen;
    QColor color = compiler.getOperationDrawingColor(this);
    pen.setColor(color);
    QPainter painter;
    painter.begin(device);
    painter.setFont(font);
    painter.setPen(pen);
    if (inBrackets) {
        painter.drawText(currentPos, compiler.getOpeningBracket());
        currentPos.setX(currentPos.x() + fm.width(compiler.getOpeningBracket()));
    }
    painter.end();
    this->_arg1->draw(device, compiler, currentPos, height, arg1IsInBrackets);
    currentPos.setX(currentPos.x() + this->_arg1->getDrawingWidth(compiler, height,
                                                                  arg1IsInBrackets));
    if (compiler.getDrawingFlags() & DrawingFlags::BINAR_SPACE_SEPARATION)
        currentPos.setX(currentPos.x() + (int) qRound((double) fm.width(compiler.getSpaceChar()) *
                                                      spaceWidth));
    painter.begin(device);
    painter.setFont(font);
    painter.setPen(pen);
    QString s = compiler.getOperationDrawingName(this);
    painter.drawText(currentPos, s);
    currentPos.setX(currentPos.x() + fm.width(s));
    painter.end();
    if (compiler.getDrawingFlags() & DrawingFlags::BINAR_SPACE_SEPARATION)
        currentPos.setX(currentPos.x() + (int) qRound((double) fm.width(compiler.getSpaceChar()) *
                                                      spaceWidth));
    this->_arg2->draw(device, compiler, currentPos, height, arg2IsInBrackets);
    currentPos.setX(currentPos.x() + this->_arg2->getDrawingWidth(compiler, height,
                                                                  arg2IsInBrackets));
    painter.begin(device);
    painter.setFont(font);
    painter.setPen(pen);
    if (inBrackets) {
        painter.drawText(currentPos, compiler.getClosingBracket());
        currentPos.setX(currentPos.x() + fm.width(compiler.getClosingBracket()));
    }
    painter.end();

    return 0;
}

template <class T>
int QBinarOperandOperation<T>::getDrawnStringWidth(const QOperationCompiler<T> &compiler,
                                                   int height, bool inBrackets) const
{
    bool arg1IsInBrackets = compiler.getOperationPriority(this) >
            compiler.getOperationPriority(this->_arg1) || (compiler.getOperationPriority(this) ==
            compiler.getOperationPriority(this->_arg1) && compiler.getOperationAssociativity(
                                                               this->_arg1) ==
                                                          QOperationAssociativity::rightToLeft);
    bool arg2IsInBrackets = compiler.getOperationPriority(this) >
            compiler.getOperationPriority(this->_arg2) || (compiler.getOperationPriority(this) ==
            compiler.getOperationPriority(this->_arg2) && compiler.getOperationAssociativity(
                                                               this->_arg2) ==
                                                          QOperationAssociativity::leftToRight);
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    QString s = compiler.getOperationDrawingName(this);
    int width = 0;
    if (inBrackets)
        width += fm.width(compiler.getOpeningBracket()) + fm.width(compiler.getClosingBracket());
    width += this->_arg1->getDrawingWidth(compiler, height, arg1IsInBrackets);
    width += this->_arg2->getDrawingWidth(compiler, height, arg2IsInBrackets);
    if (compiler.getDrawingFlags() & DrawingFlags::BINAR_SPACE_SEPARATION) {
        QChar ch = compiler.getSpaceChar();
        width += 2 * (int) qRound((double) fm.width(ch) * compiler.getDrawingBinarSpaceWidth());
    }
    width += fm.width(s);

    return width;
}
// End of QBinarOperandOperation's methods' descriptions


// QBinarFunctionOperation
template <class T>
QBinarFunctionOperation<T>::QBinarFunctionOperation(QOperation<T> *arg1, QOperation<T> *arg2) :
    QBinarOperation<T>(arg1, arg2)
{
}

template <class T>
int QBinarFunctionOperation<T>::getDefaultPriority() const
{
    return 13;
}

template <class T>
QString QBinarFunctionOperation<T>::toQString(const QOperationCompiler<T>&compiler) const
{
    return this->getDefaultSynonyms()[0] + "(" + this->_arg1->toQString(compiler) + ", "
            + this->_arg2->toQString(compiler) + ")";
}

template <class T>
bool QBinarFunctionOperation<T>::isBinaryFunctionOperation() const
{
    return true;
}

template <class T>
int QBinarFunctionOperation<T>::draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                                     const QPoint &bottomLeft, int height, bool inBrackets) const
{
    QPoint currentPos = bottomLeft;
    bool arg1IsInBrackets = compiler.getOperationPriority(this) >
            compiler.getOperationPriority(this->_arg1) || (compiler.getOperationPriority(this) ==
            compiler.getOperationPriority(this->_arg1) && compiler.getOperationAssociativity(
                                                               this->_arg1) ==
                                                          QOperationAssociativity::rightToLeft);
    bool arg2IsInBrackets = compiler.getOperationPriority(this) >
            compiler.getOperationPriority(this->_arg2) || (compiler.getOperationPriority(this) ==
            compiler.getOperationPriority(this->_arg2) && compiler.getOperationAssociativity(
                                                               this->_arg2) ==
                                                          QOperationAssociativity::rightToLeft);
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    QPen pen;
    pen.setColor(compiler.getOperationDrawingColor(this));
    QPainter painter;
    painter.begin(device);
    painter.setFont(font);
    painter.setPen(pen);
    if (inBrackets) {
        painter.drawText(currentPos, compiler.getOpeningBracket());
        currentPos.setX(currentPos.x() + fm.width(compiler.getOpeningBracket()));
    }
    QString s = compiler.getOperationDrawingName(this) + compiler.getOpeningBracket();
    painter.drawText(currentPos, s);
    currentPos.setX(currentPos.x() + fm.width(s));
    painter.end();
    this->_arg1->draw(device, compiler, currentPos, height, arg1IsInBrackets);
    currentPos.setX(currentPos.x() + this->_arg1->getDrawingWidth(compiler, height, arg1IsInBrackets));
    painter.begin(device);
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(currentPos, compiler.getBinarOperationDelimeter());
    painter.end();
    currentPos.setX(currentPos.x() + fm.width(compiler.getBinarOperationDelimeter()));
    currentPos.setX(currentPos.x() + (int) qRound((double) fm.width(compiler.getSpaceChar()) *
                                                  compiler.getDrawingBinarSpaceWidth()));
    this->_arg2->draw(device, compiler, currentPos, height, arg2IsInBrackets);
    currentPos.setX(currentPos.x() + this->_arg2->getDrawingWidth(compiler, height, arg2IsInBrackets));
    painter.begin(device);
    painter.setFont(font);
    painter.setPen(pen);
    if (inBrackets) {
        painter.drawText(currentPos, QString(compiler.getClosingBracket()) + QString(compiler.getClosingBracket()));
    } else {
        painter.drawText(currentPos, compiler.getClosingBracket());
    }

    return 0;
}

template <class T>
int QBinarFunctionOperation<T>::getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                                bool inBrackets) const
{
    bool arg1IsInBrackets = false;/* = compiler.getOperationPriority(this) >
            compiler.getOperationPriority(this->_arg1) || (compiler.getOperationPriority(this) ==
            compiler.getOperationPriority(this->_arg1) && compiler.getOperationAssociativity(this->_arg1) ==
                                                          QOperationAssociativity::rightToLeft);*/
    bool arg2IsInBrackets = true;/* = compiler.getOperationPriority(this) >
            compiler.getOperationPriority(this->_arg2) || (compiler.getOperationPriority(this) ==
            compiler.getOperationPriority(this->_arg2) && compiler.getOperationAssociativity(this->_arg2) ==
                                                          QOperationAssociativity::rightToLeft);*/
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    int width = 0;
    if (inBrackets)
        width += fm.width(compiler.getOpeningBracket()) + fm.width(compiler.getClosingBracket());
    width += fm.width(compiler.getOpeningBracket()) + fm.width(compiler.getClosingBracket());
    width += this->_arg1->getDrawingWidth(compiler, height, arg1IsInBrackets);
    width += fm.width(compiler.getBinarOperationDelimeter());
    width += (int) qRound((double) fm.width(compiler.getSpaceChar()) * compiler.getDrawingBinarSpaceWidth());
    width += this->_arg2->getDrawingWidth(compiler, height, arg2IsInBrackets);

    return width;
}
// End of QBinarFunctionOperation


// QUnarOperation
template <class T>
QUnarOperation<T>::~QUnarOperation()
{
    delete _arg;
}

template <class T>
int QUnarOperation<T>::compileFromStack(QStack <QStackUnit <T> > &stack)
{
    if (stack.isEmpty())
        return -1;
    _arg = stack.pop().op;

    return 0;
}

template <class T>
void QUnarOperation<T>::addVariablesToList(QFunction<T> &func)
{
    this->_arg->addVariablesToList(func);
}

template <class T>
void QUnarOperation<T>::connectVarLinks(QFunctionVariable<T> *var)
{
    this->_arg->connectVarLinks(var);
}

template <class T>
bool QUnarOperation<T>::isAlwaysConstant() const
{
    return this->_arg->isAlwaysConstant();
}

template <class T>
QOperation<T> *QUnarOperation<T>::getCopy() const
{
    QUnarOperation<T> *ptr = (QUnarOperation<T> *)malloc(sizeof(*this));
    byteCopy((void *)this, (void *)ptr, sizeof(*this));
    ptr->_arg = this->_arg == nullptr ? nullptr : this->_arg->getCopy();
    return ptr;
}

template <class T>
QOperation <T> *QUnarOperation<T>::optimizeIfConstant(QFunction <T> &func)
{
    if (this->_arg->isAlwaysConstant()) {
        T use = this->getResult();
        delete this;
        return new QConstOperation<T>(use);
    } else {
        this->_arg = this->_arg->optimizeIfConstant(func);
    }
    return this;
}

template <class T>
QOperation <T> *QUnarOperation<T>::optimizeSpecial(QFunction<T> &func)
{
    this->_arg = this->_arg->optimizeSpecial(func);

    return this;
}

template <class T>
QOperation <T> *QUnarOperation<T>::optimizePolynomial(QFunction<T> &func)
{
    this->_arg = this->_arg->optimizePolynomial(func);

    return this;
}
// End of QUnarOperation


// QUnarPrefixOperation
template <class T>
QUnarPrefixOperation<T>::QUnarPrefixOperation(QOperation<T> *arg)
{
    this->_arg = arg;
}
// End of QUnarPrifixOperation


// QUnarPrefixOperation
template <class T>
uint QUnarPrefixOperation<T>::getDefaultAssociativity() const
{
    return QOperationAssociativity::rightToLeft;
}

template <class T>
QString QUnarPrefixOperation<T>::toQString(const QOperationCompiler<T> &compiler) const
{
    if (compiler.getOperationPriority(this->_arg) < compiler.getOperationPriority(this))
        return compiler.getOperationMainSynonym(this) + compiler.getOpeningBracket() +
                this->_arg->toQString(compiler) + compiler.getClosingBracket();
    if (compiler.getOperationPriority(this->_arg) == compiler.getOperationPriority(this)) {
        if (compiler.getOperationAssociativity(this->_arg) == QOperationAssociativity::leftToRight) {
            return compiler.getOperationMainSynonym(this) + compiler.getOpeningBracket() +
                    this->_arg->toQString(compiler) + compiler.getClosingBracket();
        } else if (compiler.getConvetionToStringFlags() & OperationToStringConvertionFlags::ALLOW_UNAR_SPACE_SEPARATION) {
            return compiler.getOperationMainSynonym(this) + compiler.getSpaceChar() +
                    this->_arg->toQString(compiler);
        } else {
            return compiler.getOperationMainSynonym(this) + this->_arg->toQString(compiler);
        }
    }
    if (compiler.getConvetionToStringFlags() & OperationToStringConvertionFlags::ALLOW_UNAR_SPACE_SEPARATION) {
        return compiler.getOperationMainSynonym(this) + compiler.getSpaceChar() +
                this->_arg->toQString(compiler);
    } else {
        return compiler.getOperationMainSynonym(this) + this->_arg->toQString(compiler);
    }
}

template <class T>
int QUnarPrefixOperation<T>::getDefaultPriority() const
{
    return 12;
}

template <class T>
int QUnarPrefixOperation<T>::draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                                  const QPoint &bottomLeft, int height, bool inBrackets) const
{
    QPoint currentPos = bottomLeft;
    double spaceWidth = compiler.getDrawingUnarSpaceWidth();
    bool argIsInBrackets = compiler.getOperationPriority(this) >
            compiler.getOperationPriority(this->_arg) || (compiler.getOperationPriority(this) ==
            compiler.getOperationPriority(this->_arg) && compiler.getOperationAssociativity(this->_arg) ==
                                                          QOperationAssociativity::rightToLeft);
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    QPen pen;
    QColor color = compiler.getOperationDrawingColor(this);
    pen.setColor(color);
    QPainter painter;
    painter.begin(device);
    painter.setFont(font);
    painter.setPen(pen);
    if (inBrackets) {
        painter.drawText(currentPos, compiler.getOpeningBracket());
        currentPos.setX(currentPos.x() + fm.width(compiler.getOpeningBracket()));
    }
    QString s = compiler.getOperationDrawingName(this);
    painter.drawText(currentPos, s);
    currentPos.setX(currentPos.x() + fm.width(s));
    if (compiler.getDrawingFlags() & DrawingFlags::UNAR_SPACE_SEPARATION)
        currentPos.setX(currentPos.x() + (double) fm.width(compiler.getSpaceChar()) * spaceWidth);
    painter.end();
    int argWidth = this->_arg->getDrawingWidth(compiler, height, argIsInBrackets);
    this->_arg->draw(device, compiler, currentPos, height, argIsInBrackets);
    if (inBrackets) {
        currentPos.setX(currentPos.x() + argWidth);
        painter.begin(device);
        painter.setFont(font);
        painter.setPen(pen);
        painter.drawText(currentPos, compiler.getClosingBracket());
        painter.end();
    }

    return 0;
}

template <class T>
int QUnarPrefixOperation<T>::getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                             bool inBrackets) const
{
    bool argIsInBrackets = compiler.getOperationPriority(this) >
            compiler.getOperationPriority(this->_arg) || (compiler.getOperationPriority(this) ==
            compiler.getOperationPriority(this->_arg) && compiler.getOperationAssociativity(this->_arg) ==
                                                          QOperationAssociativity::rightToLeft);
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    int width = 0;
    if (inBrackets)
        width += fm.width(compiler.getOpeningBracket()) + fm.width(compiler.getClosingBracket());
    QString s = compiler.getOperationDrawingName(this);
    width += fm.width(s);
    if (compiler.getDrawingFlags() & DrawingFlags::UNAR_SPACE_SEPARATION)
        width += (int) qRound((double) fm.width(compiler.getSpaceChar()) *
                              compiler.getDrawingUnarSpaceWidth());
    width += this->_arg->getDrawingWidth(compiler, height, argIsInBrackets);

    return width;
}
// End of QUnarPrefixOperation


// Beginning of QSumOperation's methods' description
template <class T>
QSumOperation<T>::QSumOperation(QOperation<T> *arg1, QOperation<T> *arg2) :
                                QBinarOperandOperation<T>(arg1, arg2)
{

}

template <class T>
T QSumOperation<T>::getResult() const
{
    return this->_arg1->getResult() + this->_arg2->getResult();
}

template <class T>
QVector<QString> QSumOperation<T>::getDefaultSynonyms() const
{
    QVector<QString> v;
    v.push_back("+");

    return v;
}

template <class T>
int QSumOperation<T>::getDefaultPriority() const
{
    return 10;
}

template <class T>
QOperation <T> *QSumOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QSumOperation<T>((this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function)),
                                (this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function)));
}

template <class T>
QOperation <T> *QSumOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QSumOperation(this->_arg1->getDerivative(arg, function),
                             this->_arg2->getDerivative(arg, function));
}

template <class T>
QOperation <T> *QSumOperation<T>::optimizeSpecial(QFunction<T> &function)
{
    this->_arg1 = this->_arg1->optimizeSpecial(function);
    this->_arg2 = this->_arg2->optimizeSpecial(function);

    if (this->_arg1->isAlwaysConstant() && this->_arg2->isAlwaysConstant()) {
        T use = this->getResult();
        delete this;
        return new QConstOperation<T>(use);
    }
    if (this->_arg1->isAlwaysConstant() && this->_arg1->getResult() == 0) {
        QOperation <T> *use = this->_arg2->getCopy();
        delete this;
        return use;
    }
    if (this->_arg2->isAlwaysConstant() && this->_arg2->getResult() == 0) {
        QOperation <T> *use = this->_arg1->getCopy();
        delete this;
        return use;
    }

    return this;
}

template <class T>
void QSumOperation<T>::makeSumPolynomial(QVector<QOperation<T> *> &positive,
                                         QVector<QOperation<T> *> &negative)
{
    this->_arg1->makeSumPolynomial(positive, negative);
    this->_arg2->makeSumPolynomial(positive, negative);
}

template <class T>
QOperation <T> *QSumOperation<T>::optimizePolynomial(QFunction<T> &func)
{
    /*this->_arg1 = this->_arg1->optimizePolynomial(func);
    this->_arg2 = this->_arg2->optimizePolynomial(func);

    QVector<QOperation<T> *> pos; // Positive summand
    QVector<QOperation<T> *> neg; // Negative summand

    this->makeSumPolynomial(pos, neg);

    // Simplifying constants
    QVector <QOperation <T> *> constants;
    for (int i = 0; i < pos.length(); i++) {
        if (pos[i]->isAlwaysConstant()) {
            constants.push_back(pos[i]->getCopy());
            delete pos[i];
            pos.remove(i, 1);
            i--;
        }
    }
    for (int i = 0; i < neg.length(); i++) {
        if (neg[i]->isAlwaysConstant()) {
            constants.push_back(new QConstOperation<T>( - neg[i]->getResult()));
            delete neg[i];
            neg.remove(i, 1);
            i--;
        }
    }

    T constant = 0.0;
    for (int i = 0; i < constants.length(); i++)
        constant = constant + constants[i]->getResult();

    //
    // Do there all other optimization
    //

    // Combining the result of optimization into tree
    QOperation <T> *result = nullptr;
    if (pos.length() > 0) {
        result = pos[0]->getCopy();
        for (int i = 1; i < pos.length(); i++)
            result = new QSumOperation<T>(result, pos[i]->getCopy());
        for (int i = 0; i < neg.length(); i++)
            result = new QSubOperation<T>(result, neg[i]->getCopy());
    } else {
        if (neg.length() == 1) {
            result = new QNegOperation<T>(neg[0]->getCopy());
            result = result->optimize(func);
        }
        for (int i = 1; i < neg.length(); i++)
            result = new QSubOperation<T>(result, neg[i]->getCopy());
    }

    if (result != nullptr) {
        if (constant > 0.0)
            result = new QSumOperation<T>(result, new QConstOperation<T>(constant));
        else if (constant < 0.0)
            result = new QSubOperation<T>(result, new QConstOperation<T>(constant));
    } else {
        result = new QConstOperation<T>(constant);
    }


    clearQVector(pos);
    clearQVector(neg);
    clearQVector(constants);*/

    return this;
}
// End of QSumOperation's methods' description


// Beginning of QSubOperation's methods' description
template <class T>
QSubOperation<T>::QSubOperation(QOperation<T> *arg1, QOperation<T> *arg2)
                                : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QSubOperation<T>::getResult() const
{
    return this->_arg1->getResult() - this->_arg2->getResult();
}

template <class T>
QVector<QString> QSubOperation<T>::getDefaultSynonyms() const
{
    QVector<QString> v;
    v.push_back("-");

    return v;
}

template <class T>
int QSubOperation<T>::getDefaultPriority() const
{
    return 10;
}

template <class T>
QOperation <T> *QSubOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QSubOperation<T>((this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function)),
            (this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function)));
}

template <class T>
QOperation <T> *QSubOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QSubOperation<T>(this->_arg1->getDerivative(arg, function),
                                this->_arg2->getDerivative(arg, function));
}

template <class T>
QOperation <T> *QSubOperation<T>::optimizeSpecial(QFunction<T> &function)
{
    this->_arg1 = this->_arg1->optimizeSpecial(function);
    this->_arg2 = this->_arg2->optimizeSpecial(function);

    if (this->_arg1->isAlwaysConstant() && this->_arg2->isAlwaysConstant()) {
        T use = this->getResult();
        delete this;
        return new QConstOperation <T>(use);
    }
    if (this->_arg1->isAlwaysConstant() && this->_arg1->getResult() == 0) {
        QOperation <T> *use = new QNegOperation<T>(this->_arg2->getCopy());
        delete this;
        return use;
    }
    if (this->_arg2->isAlwaysConstant() && this->_arg2->getResult() == 0) {
        QOperation <T> *use = this->_arg1->getCopy();
        delete this;
        return use;
    }
    if (this->_arg2->isAlwaysConstant() && this->_arg2->getResult() < 0.0) {
        QOperation <T> *use1 = this->_arg1->getCopy();
        QOperation <T> *use2 = new QNegOperation<T>(this->_arg2->getCopy());
        delete this;
        use2 = use2->optimize(function);
        return new QSumOperation<T>(use1, use2);
    }

    return this;
}

template <class T>
void QSubOperation<T>::makeSumPolynomial(QVector<QOperation<T> *> &positive,
                                         QVector<QOperation<T> *> &negative)
{
    this->_arg1->makeSumPolynomial(positive, negative);
    this->_arg2->makeSumPolynomial(negative, positive);
}
// End of QSumOperation's methods' description


// Beginning of QMulOperation's methods' description
template <class T>
QMulOperation<T>::QMulOperation(QOperation<T> *arg1, QOperation<T> *arg2) :
                                QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QMulOperation<T>::getResult() const
{
    T x = this->_arg1->getResult();
    T y = this->_arg2->getResult();
    if (x == 0.0 || y == 0.0)
        return 0.0;
    else
        return x * y;
}

template <class T>
QVector<QString> QMulOperation<T>::getDefaultSynonyms() const
{
    QVector<QString> v;
    v.push_back("*");

    return v;
}

template <class T>
int QMulOperation<T>::getDefaultPriority() const
{
    return 11;
}

template <class T>
QString QMulOperation<T>::toQString() const
{
    if (this->_arg1->isAlwaysConstant() && this->_arg2->getDefaultSynonyms()[0][0].isLetter())
        return this->_arg1->toQString() + this->_arg2->toQString();
    else {
        QString s1, s2;
        if (this->_arg1->getDefaultPriority() < this->getDefaultPriority())
            s1 = this->OPENING_BRACKET + this->_arg1->toQString() + this->CLOSING_BRACKET;
        else if (this->_arg1->getDefaultPriority() == this->getDefaultPriority() &&
                 this->getDefaultAssociativity() == QOperationAssociativity::rightToLeft)
            s1 = this->OPENING_BRACKET + this->_arg1->toQString() + this->CLOSING_BRACKET;
        else
            s1 = this->_arg1->toQString();

        if (this->_arg2->getDefaultPriority() < this->getDefaultPriority())
            s2 = this->OPENING_BRACKET + this->_arg2->toQString() + this->CLOSING_BRACKET;
        else if (this->_arg2->getDefaultPriority() == this->getDefaultPriority() &&
                 this->getDefaultAssociativity() == QOperationAssociativity::leftToRight)
            s2 = this->OPENING_BRACKET + this->_arg2->toQString() + this->CLOSING_BRACKET;
        else
            s2 = this->_arg2->toQString();

        return s1 + " " + this->getDefaultSynonyms()[0] + " " + s2;
    }
}

template <class T>
bool QMulOperation<T>::operationStartsHere(const QString &s, int pos, QFunction <T> &function) const
{
    if (QOperation<T>::operationStartsHere(s, pos, function))
        return true;

    return false;
}

template <class T>
int QMulOperation<T>::prepareQString(QString &s, const QOperationCompiler<T> &compiler) const
{
    if (compiler.getCompilationFlags() & CompilationFlags::ALLOW_UNSIGNED_MULTIPLICATION) {
        int pos = 0;
        QOperation <T> *op1, *op2;
        QConstOperation <T> constOp;
        QVarOperation <T> varOp(nullptr);
        op1 = compiler.getOperationFromString(s, pos);
        while (pos < s.length()) {
            int oldPos = pos;
            op2 = compiler.getOperationFromString(s, pos);
            if (op2 == nullptr) {
                pos++;
                continue;
            }
            if (op1 == nullptr) {
                op1 = op2;
                continue;
            }
            QString ins = QString(" ") + compiler.getContextMap()[name()].getSynonyms()[0] +
                    QString(" ");
            if (op1->name() == constOp.name() && op2->name() == varOp.name()) { // Const * Var
                s = s.insert(oldPos, ins);
                pos += ins.length();
            }
            if (op1->name() == constOp.name() && op2->name() == constOp.name()) {
                s = s.insert(oldPos, ins);
                pos += ins.length();
            }
            if (op1->name() == constOp.name() && op2->getArgumentNum() == 1) {
                s = s.insert(oldPos, ins);
                pos += ins.length();
            }
            if (op1 != nullptr)
                delete op1;
            op1 = op2;
        }
        if (op1 != nullptr)
            delete op1;
    }

    return 0;
}

template <class T>
QOperation <T> *QMulOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QMulOperation<T>((this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function)),
                               (this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function)));
}

template <class T>
QOperation <T> *QMulOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QSumOperation<T>(new QMulOperation<T>(this->_arg1->getCopy(),
                                                     this->_arg2->getDerivative(arg, function)),
                                new QMulOperation<T>(this->_arg1->getDerivative(arg, function),
                                                     this->_arg2->getCopy()));
}

template <class T>
QOperation <T> *QMulOperation<T>::optimizeSpecial(QFunction <T> &func)
{
    this->_arg1 = this->_arg1->optimizeSpecial(func);
    this->_arg2 = this->_arg2->optimizeSpecial(func);

    if (this->_arg1->isAlwaysConstant() && this->_arg2->isAlwaysConstant()) {
        T use = this->getResult();
        delete this;
        return new QConstOperation <T>(use);
    }
    if (this->_arg1->isAlwaysConstant() && this->_arg1->getResult() == 0.0) {
        delete this;
        return new QConstOperation<T>(0.0);
    }
    if (this->_arg2->isAlwaysConstant() && this->_arg2->getResult() == 0.0) {
        delete this;
        return new QConstOperation<T>(0.0);
    }
    if (this->_arg1->isAlwaysConstant() && this->_arg1->getResult() == 1.0) {
        QOperation <T> *use = this->_arg2->getCopy();
        delete this;
        return use;
    }
    if (this->_arg2->isAlwaysConstant() && this->_arg2->getResult() == 1.0) {
        QOperation <T> *use = this->_arg1->getCopy();
        delete this;
        return use;
    }
    if (this->_arg1->isAlwaysConstant() && this->_arg1->getResult() == -1.0) {
        QOperation <T> *use = new QNegOperation<T>(this->_arg2->getCopy());
        delete this;
        return use;
    }
    if (this->_arg2->isAlwaysConstant() && this->_arg2->getResult() == -1.0) {
        QOperation <T> *use = new QNegOperation<T>(this->_arg1->getCopy());
        delete this;
        return use;
    }

    return this;
}
// End of QSumOperation's methods' description


// QDivOperation
template <class T>
QDivOperation<T>::QDivOperation(QOperation<T> *arg1, QOperation<T> *arg2) :
                                QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QDivOperation<T>::getResult() const
{
    return this->_arg1->getResult() / this->_arg2->getResult();
}

template <class T>
QVector <QString> QDivOperation<T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("/");

    return v;
}

template <class T>
int QDivOperation<T>::getDefaultPriority() const
{
    return 11;
}

template <class T>
QOperation <T> *QDivOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QDivOperation<T>((this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function)),
            (this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function)));
}

template <class T>
QOperation <T> *QDivOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QDivOperation<T>(new QSubOperation<T>(new QMulOperation<T>(
                                                         this->_arg1->getDerivative(arg, function),
                                                         this->_arg2->getCopy()),
                                                     new QMulOperation<T>(
                                                         this->_arg1->getCopy(),
                                                        this->_arg2->getDerivative(arg, function))),
                                new QPowOperation<T>(this->_arg2->getCopy(),
                                                     new QConstOperation<T>(2.0)));
}

template <class T>
QOperation <T> *QDivOperation<T>::optimizeSpecial(QFunction<T> &function)
{
    this->_arg1 = this->_arg1->optimizeSpecial(function);
    this->_arg2 = this->_arg2->optimizeSpecial(function);

    if (this->_arg1->isAlwaysConstant() && this->_arg2->isAlwaysConstant()) {
        T use = this->getResult();
        delete this;
        return new QConstOperation <T>(use);
    }
    if (this->_arg1->isAlwaysConstant() && this->_arg1->getResult() == 0.0) {
        delete this;
        return new QConstOperation<T>(0.0);
    }
    if (this->_arg2->isAlwaysConstant() && this->_arg2->getResult() == 1.0) {
        QOperation <T> *use = this->_arg1->getCopy();
        delete this;
        return use;
    }
    if (this->_arg2->isAlwaysConstant() && this->_arg2->getResult() == -1.0) {
        QOperation <T> *use = new QNegOperation<T>(this->_arg1->getCopy());
        delete this;
        return use;
    }

    return this;
}
/*
template <class T>
int QDivOperation<T>::draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                           const QPoint &bottomLeft, int height, bool inBrackets) const
{
    QPoint currentPos = bottomLeft;
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    QPen pen;
    QColor color = compiler.getOperationDrawingColor(this);
    pen.setColor(color);
    QPainter painter;
    painter.begin(device);
    painter.setFont(font);
    painter.setPen(pen);
    if (compiler.getDrawingFlags() & DrawingFlags::DRAW_SLASH_FRACTION) {
        QConstOperation<T> constOp;
        QVarOperation<T> varOp;
        QString constName = constOp.name();
        QString varName = varOp.name();
        double ratio = 0.6;
        int h = (int) qRound((double) height * ratio);
        double fractXRatio = 0.3;
        double fractYRatio = 0.8;
        int fractX = (int) qRound((double) height * fractXRatio);
        int fractY = (int) qRound((double) height * fractYRatio);
        if ((compiler.getDrawingFlags() & DrawingFlags::ONLY_SIMPLE_FRACTION_SLASH) &&
                (this->_arg1->name() == constName || this->_arg1->name() == varName) &&
                (this->_arg2->name() == constName || this->_arg2->name() == varName)) {
            if (inBrackets) {
                painter.drawText(currentPos, compiler.getOpeningBracket());
                currentPos.setX(currentPos.x() + fm.width(compiler.getOpeningBracket()));
            }
            currentPos.setY(currentPos.y() - height + h);
            painter.end();
            this->_arg1->draw(device, compiler, currentPos, h, false);
            currentPos.setX(currentPos.x() + this->_arg1->getDrawingWidth(compiler, h, false));
            currentPos.setY(currentPos.y() + height - h);
            painter.begin(device);
            painter.setFont(font);
            painter.setPen(pen);
            QPoint p1, p2;
            p1.setX(currentPos.x());
            p2.setX(currentPos.x() + fractX);
            p1.setY(currentPos.y() - (height - fractY) / 2);
            p2.setY(p1.y() - fractY);
            painter.drawLine(p1, p2);
            painter.end();
            currentPos.setY(currentPos.y() + fractY);
            this->_arg2->draw(device, compiler, currentPos, h, false);
            return 0;
        }

    }

    return 0;
}

template <class T>
int QDivOperation<T>::getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                      bool inBrackets) const
{
    int width = 0;
    QPoint currentPos = bottomLeft;
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    QPen pen;
    QColor color = compiler.getOperationDrawingColor(this);
    pen.setColor(color);
    QPainter painter;
    painter.begin(device);
    painter.setFont(font);
    painter.setPen(pen);
    if (compiler.getDrawingFlags() & DrawingFlags::DRAW_SLASH_FRACTION) {
        QConstOperation<T> constOp;
        QVarOperation<T> varOp;
        QString constName = constOp.name();
        QString varName = varOp.name();
        double ratio = 0.6;
        int h = (int) qRound((double) height * ratio);
        double fractXRatio = 0.3;
        double fractYRatio = 0.8;
        int fractX = (int) qRound((double) height * fractXRatio);
        int fractY = (int) qRound((double) height * fractYRatio);
        if ((compiler.getDrawingFlags() & DrawingFlags::ONLY_SIMPLE_FRACTION_SLASH) &&
                (this->_arg1->name() == constName || this->_arg1->name() == varName) &&
                (this->_arg2->name() == constName || this->_arg2->name() == varName)) {
            if (inBrackets) {
                painter.drawText(currentPos, compiler.getOpeningBracket());
                currentPos.setX(currentPos.x() + fm.width(compiler.getOpeningBracket()));
            }
            currentPos.setY(currentPos.y() - height + h);
            painter.end();
            this->_arg1->draw(device, compiler, currentPos, h, false);
            currentPos.setX(currentPos.x() + this->_arg1->getDrawingWidth(compiler, h, false));
            currentPos.setY(currentPos.y() + height - h);
            painter.begin(device);
            painter.setFont(font);
            painter.setPen(pen);
            QPoint p1, p2;
            p1.setX(currentPos.x());
            p2.setX(currentPos.x() + fractX);
            p1.setY(currentPos.y() - (height - fractY) / 2);
            p2.setY(p1.y() - fractY);
            painter.drawLine(p1, p2);
            painter.end();
            currentPos.setY(currentPos.y() + fractY);
            this->_arg2->draw(device, compiler, currentPos, h, false);
            return 0;
        }

    }
}*/
// End of QDivOperation


// QExpOperation
template <class T>
QExpOperation<T>::QExpOperation(QOperation<T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QExpOperation<T>::getResult() const
{
    return exp(this->_arg->getResult());
}

template <class T>
QVector <QString> QExpOperation<T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("exp");
    v.push_back("Exp");

    return v;
}

template <class T>
QOperation <T> *QExpOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QExpOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QExpOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QMulOperation<T>(this->_arg->getDerivative(arg, function),
                                new QExpOperation<T>(this->_arg->getCopy()));
}
// End of QExpOperation


// QSinOperation
template <class T>
QSinOperation<T>::QSinOperation(QOperation<T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QSinOperation<T>::getResult() const
{
    return sin(this->_arg->getResult());
}

template <class T>
QVector <QString> QSinOperation<T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("sin");
    v.push_back("sinus");
    v.push_back("Sin");
    v.push_back("Sinus");

    return v;
}

template <class T>
QOperation <T> *QSinOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QSinOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QSinOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QMulOperation<T>(this->_arg->getDerivative(arg, function),
                                new QCosOperation<T>(this->_arg->getCopy()));
}

// End of QSinOperation


// QCosOperation
template <class T>
QCosOperation<T>::QCosOperation(QOperation<T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QCosOperation<T>::getResult() const
{
    return cos(this->_arg->getResult());
}

template <class T>
QVector <QString> QCosOperation<T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("cos");
    v.push_back("Cos");

    return v;
}

template <class T>
QOperation <T> *QCosOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QCosOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QCosOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QNegOperation<T>(new QMulOperation<T>(this->_arg->getDerivative(arg, function),
                                                     new QSinOperation<T>(
                                                         this->_arg->getCopy())));
}
// End of QCosOperation


// QTanOperation
template <class T>
QTgOperation<T>::QTgOperation(QOperation<T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QTgOperation<T>::getResult() const
{
    return tan(this->_arg->getResult());
}

template <class T>
QVector <QString> QTgOperation<T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("tg");
    v.push_back("tan");
    v.push_back("Tg");
    v.push_back("Tan");

    return v;
}

template <class T>
QOperation <T> *QTgOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QTgOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QTgOperation<T>::getDerivative(const QString &arg
                                               , QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
                                new QPowOperation<T>(new QCosOperation<T>(
                                                         this->_arg->getCopy()),
                                                     new QConstOperation<T>(2.0)));
}
// End of QTanOperation


// QCtanOperation
template <class T>
QCtgOperation<T>::QCtgOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QCtgOperation<T>::getResult() const
{
    return 1 / tan(this->_arg->getResult());
}

template <class T>
QVector <QString> QCtgOperation<T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("ctg");
    v.push_back("cot");
    v.push_back("Ctg");
    v.push_back("Cot");

    return v;
}

template <class T>
QOperation <T> *QCtgOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QCtgOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QCtgOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QDivOperation<T>(new QNegOperation<T>(this->_arg->getDerivative(arg, function)),
                                new QPowOperation<T>(new QSinOperation<T>(
                                                         this->_arg->getCopy()),
                                                     new QConstOperation<T>(2.0)));
}
// End of QCtanOperation


// QSqrtOperation
template <class T>
QSqrtOperation<T>::QSqrtOperation(QOperation<T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QSqrtOperation<T>::getResult() const
{
    return sqrt(this->_arg->getResult());
}

template <class T>
QVector <QString> QSqrtOperation<T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("sqrt");
    v.push_back("Sqrt");

    return v;
}

template <class T>
QOperation <T> *QSqrtOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QSqrtOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QSqrtOperation<T>::getDerivative(const QString &arg,
                                                 QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
                                new QMulOperation<T>(new QConstOperation<T>(2.0),
                                                     new QSqrtOperation<T>(
                                                         this->_arg->getCopy())));
}

template <class T>
int QSqrtOperation<T>::draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                            const QPoint &bottomLeft, int height, bool inBrackets) const
{
    if (compiler.getDrawingFlags() & DrawingFlags::DRAW_RADICAL) {
        QPainter painter;
        QPen pen;
        QColor color = compiler.getOperationDrawingColor(this);
        pen.setWidthF((double) height * 0.04);
        pen.setColor(color);
        pen.setCapStyle(Qt::RoundCap);
        int h = qRound((double) height * 0.8);
        QPolygon polygon;
        QPoint p = bottomLeft;
        p.setY(p.y() - height / 2);
        polygon << p;
        p.setX(p.x() + qRound((double) height * 0.15));
        polygon << p;
        p.setX(p.x() + qRound((double) height * 0.07));
        p.setY(bottomLeft.y() - qRound((double) height * 0.07));
        polygon << p;
        p.setX(p.x() + qRound((double) height * 0.07));
        p.setY(bottomLeft.y() - qRound((double) height * 0.93));
        polygon << p;
        p.setX(p.x() + qRound((double) height * 0.1));
        QPoint P;
        P.setX(p.x());
        P.setY(bottomLeft.y() - qRound((double) height * 0.07));
        this->_arg->draw(device, compiler, P, h, false);
        p.setX(p.x() + this->_arg->getDrawingWidth(compiler, h, false) + qRound((double) height * 0.1));
        polygon << p;
        p.setY(p.y() + qRound((double) height * 0.07));
        polygon << p;
        painter.begin(device);
        painter.setRenderHints(QPainter::Antialiasing);
        painter.setPen(pen);
        painter.drawPolyline(polygon);
        painter.end();
        return 0;
    } else {
        QPoint currentPos = bottomLeft;
        double spaceWidth = compiler.getDrawingUnarSpaceWidth();
        bool argIsInBrackets = compiler.getOperationPriority(this) >
                compiler.getOperationPriority(this->_arg) || (compiler.getOperationPriority(this) ==
                compiler.getOperationPriority(this->_arg) && compiler.getOperationAssociativity(this->_arg) ==
                                                              QOperationAssociativity::rightToLeft);
        QFont font = compiler.getDrawingFont();
        font.setPixelSize(height);
        QFontMetrics fm(font);
        QPen pen;
        QColor color = compiler.getOperationDrawingColor(this);
        pen.setColor(color);
        QPainter painter;
        painter.begin(device);
        painter.setFont(font);
        painter.setPen(pen);
        if (inBrackets) {
            painter.drawText(currentPos, compiler.getOpeningBracket());
            currentPos.setX(currentPos.x() + fm.width(compiler.getOpeningBracket()));
        }
        QString s = compiler.getOperationDrawingName(this);
        painter.drawText(currentPos, s);
        currentPos.setX(currentPos.x() + fm.width(s));
        if (compiler.getDrawingFlags() & DrawingFlags::UNAR_SPACE_SEPARATION)
            currentPos.setX(currentPos.x() + (double) fm.width(compiler.getSpaceChar()) * spaceWidth);
        painter.end();
        int argWidth = this->_arg->getDrawingWidth(compiler, height, argIsInBrackets);
        this->_arg->draw(device, compiler, currentPos, height, argIsInBrackets);
        if (inBrackets) {
            currentPos.setX(currentPos.x() + argWidth);
            painter.begin(device);
            painter.setFont(font);
            painter.setPen(pen);
            painter.drawText(currentPos, compiler.getClosingBracket());
            painter.end();
        }

        return 0;
    }
}

template <class T>
int QSqrtOperation<T>::getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                       bool inBrackets) const
{
    if (compiler.getDrawingFlags() & DrawingFlags::DRAW_RADICAL) {
        int width = 0;
        width += qRound((double) height * 0.5);
        width += this->_arg->getDrawingWidth(compiler, qRound((double) height * 0.8), false);

        return width;
    } else {
        bool argIsInBrackets = compiler.getOperationPriority(this) >
                compiler.getOperationPriority(this->_arg) || (compiler.getOperationPriority(this) ==
                compiler.getOperationPriority(this->_arg) && compiler.getOperationAssociativity(this->_arg) ==
                                                              QOperationAssociativity::rightToLeft);
        QFont font = compiler.getDrawingFont();
        font.setPixelSize(height);
        QFontMetrics fm(font);
        int width = 0;
        if (inBrackets)
            width += fm.width(compiler.getOpeningBracket()) + fm.width(compiler.getClosingBracket());
        QString s = compiler.getOperationDrawingName(this);
        width += fm.width(s);
        if (compiler.getDrawingFlags() & DrawingFlags::UNAR_SPACE_SEPARATION)
            width += (int) qRound((double) fm.width(compiler.getSpaceChar()) *
                                  compiler.getDrawingUnarSpaceWidth());
        width += this->_arg->getDrawingWidth(compiler, height, argIsInBrackets);

        return width;

    }
}
// End of QSqtrOperation


// QSignOperation
template <class T>
QSignOperation<T>::QSignOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QSignOperation<T>::getResult() const
{
    if (this->_arg->getResult() < 0.0)
        return -1.0;
    else if (this->_arg->getResult() > 0.0)
        return 1.0;

    return 0.0;
}

template <class T>
QVector <QString> QSignOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("sign");
    v.push_back("Sign");

    return v;
}

template <class T>
QOperation <T> *QSignOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QSignOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QSignOperation<T>::getDerivative(const QString &,
                                                 QFunction<T> &) const
{
    return new QConstOperation<T>(0.0);
}
// End of QSignOperation


// QPowOperation
template <class T>
QPowOperation<T>::QPowOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QPowOperation<T>::getResult() const
{
    return pow(this->_arg1->getResult(), this->_arg2->getResult());
}

template <class T>
QVector <QString> QPowOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("^");

    return v;
}

template <class T>
int QPowOperation<T>::getDefaultPriority() const
{
    return 12;
}

template <class T>
uint QPowOperation<T>::getDefaultAssociativity() const
{
    return QOperationAssociativity::rightToLeft;
}

template <class T>
QOperation <T> *QPowOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QMulOperation<T>(this->getCopy(),
                                new QSumOperation<T>(new QMulOperation<T>(
                                                         this->_arg1->getDerivative(arg, function),
                                                         new QDivOperation<T>(
                                                             this->_arg2->getCopy(),
                                                             this->_arg1->getCopy())),
                                                     new QMulOperation<T>(
                                                         this->_arg2->getDerivative(arg, function),
                                                         new QLnOperation<T>(
                                                             this->_arg1->getCopy()))));
}

template <class T>
QOperation <T> *QPowOperation<T>::optimizeSpecial(QFunction<T> &)
{
    QOperation <T> *use = this;

    return use;
}
// End of QPowOperation


// QRootOperation
template <class T>
QRootOperation<T>::QRootOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarFunctionOperation<T>(arg1, arg2)
{
}

template <class T>
T QRootOperation<T>::getResult() const
{
    return pow(this->_arg1->getResult(), 1 / (this->_arg2->getResult()));
}

template <class T>
QVector <QString> QRootOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("root");
    v.push_back("Root");

    return v;
}

template <class T>
QOperation <T> *QRootOperation<T>::getDerivative(const QString &arg,
                                                 QFunction<T> &function) const
{
    return new QMulOperation<T>(new QRootOperation<T>(this->_arg1->getCopy(),
     this->_arg2->getCopy()),
    new QSubOperation<T>(new QDivOperation<T>(this->_arg1->getDerivative(arg, function),
    new QMulOperation<T>(this->_arg1->getCopy(),
     this->_arg2->getCopy())),
     new QDivOperation<T>(new QMulOperation<T>(this->_arg2->getDerivative(arg, function),
     new QLnOperation<T>(this->_arg1->getCopy())),
     new QPowOperation<T>(this->_arg2->getCopy(),
    new QConstOperation<T>(2)))));
}
// End of QRootOperation


// QLnOperation
template <class T>
QLnOperation<T>::QLnOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QLnOperation<T>::getResult() const
{
    return log(this->_arg->getResult());
}

template <class T>
QVector <QString> QLnOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("ln");
    v.push_back("Ln");

    return v;
}

template <class T>
QOperation <T> *QLnOperation<T>::getDerivative(const QString &arg,
                                               QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
                                this->_arg->getCopy());
}
// End of QLnOperation


// QLbOperation
template <class T>
QLbOperation<T>::QLbOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QLbOperation<T>::getResult() const
{
    return log2(this->_arg->getResult());
}

template <class T>
QVector <QString> QLbOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("lb");
    v.push_back("Lb");

    return v;
}

template <class T>
QOperation <T> *QLbOperation<T>::getDerivative(const QString &arg,
                                               QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
 new QMulOperation<T>(this->_arg->getCopy(),
 new QLnOperation<T>(new QConstOperation<T>(2.0))));
}
// End of QLbOperation


// QLgOperation
template <class T>
QLgOperation<T>::QLgOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QLgOperation<T>::getResult() const
{
    return log10(this->_arg->getResult());
}

template <class T>
QVector <QString> QLgOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("lg");
    v.push_back("Lg");

    return v;
}

template <class T>
QOperation <T> *QLgOperation<T>::getDerivative(const QString &arg,
                                               QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
                                new QMulOperation<T>(this->_arg->getCopy(),
                                                     new QLnOperation<T>(
                                                         new QConstOperation<T>(10.0))));
}
// End of QLgOperation


// QLogOperation
template <class T>
QLogOperation<T>::QLogOperation(QOperation <T> *arg1, QOperation <T> *arg2) :
    QBinarFunctionOperation<T>(arg1, arg2)
{
}

template <class T>
T QLogOperation<T>::getResult() const
{
    return log(this->_arg1->getResult()) / log(this->_arg2->getResult());
}

template <class T>
QVector <QString> QLogOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("log");
    v.push_back("Log");

    return v;
}

template <class T>
QOperation <T> *QLogOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QDivOperation<T>(new QSubOperation<T>(
                                    new QMulOperation<T>(
                                        new QDivOperation<T>(
                                            this->_arg2->getDerivative(arg, function),
                                                          this->_arg2->getCopy()),
                                                          new QLnOperation<T>(
                                            this->_arg1->getCopy())),
                                                          new QMulOperation<T>(
                                        new QDivOperation<T>(
                                            this->_arg1->getDerivative(arg, function),
                                                          this->_arg1->getCopy()),
                                                          new QLnOperation<T>(
                                            this->_arg2->getCopy()))),
                                                          new QPowOperation<T>(
                                    new QLnOperation<T>(this->_arg1->getCopy()),
                                    new QConstOperation<T>(2.0)));
}
// End of QLogOperation


// QArcsinOperation
template <class T>
QArcsinOperation<T>::QArcsinOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QArcsinOperation<T>::getResult() const
{
    return asin(this->_arg->getResult());
}

template <class T>
QVector <QString> QArcsinOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("arcsin");
    v.push_back("Arcsin");
    v.push_back("asin");
    v.push_back("Asin");

    return v;
}

template <class T>
QOperation <T> *QArcsinOperation<T>::getDerivative(const QString &arg,
                                                   QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
 new QSqrtOperation<T>(new QSubOperation<T>(new QConstOperation<T>(1),
 this->_arg->getCopy())));
}
// End of QArcsinOperation


// QArccosOperation
template <class T>
QArccosOperation<T>::QArccosOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QArccosOperation<T>::getResult() const
{
    return acos(this->_arg->getResult());
}

template <class T>
QVector <QString> QArccosOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("arccos");
    v.push_back("Arccos");
    v.push_back("acos");
    v.push_back("Acos");

    return v;
}

template <class T>
QOperation <T> *QArccosOperation<T>::getDerivative(const QString &arg,
                                                   QFunction<T> &function) const
{
    return new QNegOperation<T>(new QDivOperation<T>(this->_arg->getDerivative(arg, function),
 new QSqrtOperation<T>(new QSubOperation<T>(new QConstOperation<T>(1),
 new QPowOperation<T>(this->_arg->getCopy(), new QConstOperation<T>(2))))));
}
// End of QArccosOperation


// QArctgOperation
template <class T>
QArctgOperation<T>::QArctgOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QArctgOperation<T>::getResult() const
{
    return atan(this->_arg->getResult());
}

template <class T>
QVector <QString> QArctgOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("arctg");
    v.push_back("Arctg");
    v.push_back("atan");
    v.push_back("Atan");

    return v;
}

template <class T>
QOperation <T> *QArctgOperation<T>::getDerivative(const QString &arg,
                                                  QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
 new QSumOperation<T>(new QConstOperation<T>(1),
new QPowOperation<T>(this->_arg->getCopy(),
 new QConstOperation<T>(2))));
}
// End of QArctgOperation


// QArcctgOperation
template <class T>
QArcctgOperation<T>::QArcctgOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QArcctgOperation<T>::getResult() const
{
    return atan(1 / this->_arg->getResult());
}

template <class T>
QVector <QString> QArcctgOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("arcctg");
    v.push_back("Arcctg");
    v.push_back("acot");
    v.push_back("Acot");

    return v;
}

template <class T>
QOperation <T> *QArcctgOperation<T>::getDerivative(const QString &arg,
                                                   QFunction<T> &function) const
{
    return new QNegOperation<T>(new QDivOperation<T>(this->_arg->getDerivative(arg, function),
 new QSumOperation<T>(new QConstOperation<T>(1),
new QPowOperation<T>(this->_arg->getCopy(),
 new QConstOperation<T>(2)))));
}
// End of QArcctgOperation


// QSecOperation
template <class T>
QSecOperation<T>::QSecOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QSecOperation<T>::getResult() const
{
    return 1/cos(this->_arg->getResult());
}

template <class T>
QVector <QString> QSecOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("sec");
    v.push_back("Sec");
    v.push_back("scs");
    v.push_back("Scs");

    return v;
}

template <class T>
QOperation <T> *QSecOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QMulOperation<T>(this->_arg->getDerivative(arg, function),
 new QMulOperation<T>(new QTgOperation<T>(this->_arg->getCopy()),
 new QSecOperation<T>(this->_arg->getCopy())));
}
// End of QSecOperation


// QCosecOperation
template <class T>
QCosecOperation<T>::QCosecOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QCosecOperation<T>::getResult() const
{
    return 1 / sin(this->_arg->getResult());
}

template <class T>
QVector <QString> QCosecOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("cosec");
    v.push_back("Cosec");
    v.push_back("coscs");
    v.push_back("Coscs");

    return v;
}

template <class T>
QOperation <T> *QCosecOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QCosecOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QCosecOperation<T>::getDerivative(const QString &arg,
                                                  QFunction<T> &function) const
{
    return new QNegOperation<T>(new QMulOperation<T>(this->_arg->getDerivative(arg, function),
 new QMulOperation<T>(new QCtgOperation<T>(this->_arg->getCopy()),
 new QCosecOperation<T>(this->_arg->getCopy()))));
}
// End of QCosecOperation


// QAbsOperation
template <class T>
QAbsOperation<T>::QAbsOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QAbsOperation<T>::getResult() const
{
    return fabs(this->_arg->getResult());
}

template <class T>
QVector <QString> QAbsOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("abs");
    v.push_back("Abs");

    return v;
}

template <class T>
int QAbsOperation<T>::prepareQString(QString &, QFunction<T> &)
{

return 0;
}

template <class T>
QOperation <T> *QAbsOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QAbsOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QAbsOperation<T>::getDerivative(const QString &,
                                                QFunction<T> &function) const
{
    return new QSignOperation<T>(this->_arg->getCopy());
}
// End of QAbsOperation


// QNotOperation
template <class T>
QNotOperation<T>::QNotOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QNotOperation<T>::getResult() const
{
    return !static_cast<bool>(this->_arg->getResult());
}

template <class T>
QVector <QString> QNotOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("!");
    v.push_back("not");
    v.push_back("Not");
    v.push_back("NOT");

    return v;
}

template <class T>
QOperation <T> *QNotOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QNotOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QNotOperation<T>::getDerivative(const QString &,
                                                QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QNotOperation


// QLessOperation
template <class T>
QLessOperation<T>::QLessOperation(QOperation <T> *arg1, QOperation <T> *arg2) :
    QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QLessOperation<T>::getResult() const
{
    return this->_arg1->getResult() < this->_arg2->getResult();
}

template <class T>
QVector <QString> QLessOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("<");

    return v;
}

template <class T>
int QLessOperation<T>::getDefaultPriority() const
{
    return 8;
}

template <class T>
QOperation <T> *QLessOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QLessOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QLessOperation<T>::getDerivative(const QString &,
                                                 QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QLessOperation


// QEqualOperation
template <class T>
QEqualOperation<T>::QEqualOperation(QOperation <T> *arg1, QOperation <T> *arg2) :
    QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QEqualOperation<T>::getResult() const
{
    return this->_arg1->getResult() == this->_arg2->getResult();
}

template <class T>
QVector <QString> QEqualOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("=");

    return v;
}

template <class T>
int QEqualOperation<T>::getDefaultPriority() const
{
    return 7;
}

template <class T>
QOperation <T> *QEqualOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QEqualOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QEqualOperation<T>::getDerivative(const QString &,
                                                  QFunction<T> &) const
{
    return new QConstOperation<T>(0.0);
}
// End of QEqualOperation


// QNotequalOperation
template <class T>
QNotequalOperation<T>::QNotequalOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QNotequalOperation<T>::getResult() const
{
    return this->_arg1->getResult() != this->_arg2->getResult();
}

template <class T>
QVector <QString> QNotequalOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("!=");

    return v;
}

template <class T>
int QNotequalOperation<T>::getDefaultPriority() const
{
    return 7;
}

template <class T>
QOperation <T> *QNotequalOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QNotequalOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QNotequalOperation<T>::getDerivative(const QString &,
                                                     QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QNotequalOperation


// QOverOperation
template <class T>
QOverOperation<T>::QOverOperation(QOperation <T> *arg1, QOperation <T> *arg2) :
    QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QOverOperation<T>::getResult() const
{
    return this->_arg1->getResult() > this->_arg2->getResult();
}

template <class T>
QVector <QString> QOverOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back(">");

    return v;
}

template <class T>
int QOverOperation<T>::getDefaultPriority() const
{
    return 8;
}

template <class T>
QOperation <T> *QOverOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QOverOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QOverOperation<T>::getDerivative(const QString &,
                                                 QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QOverOperation


// QNotoverOperation
template <class T>
QNotoverOperation<T>::QNotoverOperation(QOperation <T> *arg1, QOperation <T> *arg2) :
    QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QNotoverOperation<T>::getResult() const
{
    return this->_arg1->getResult() <= this->_arg2->getResult();
}

template <class T>
QVector <QString> QNotoverOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("<=");

    return v;
}

template <class T>
int QNotoverOperation<T>::getDefaultPriority() const
{
    return 8;
}

template <class T>
QOperation <T> *QNotoverOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QNotoverOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QNotoverOperation<T>::getDerivative(const QString &,
                                                    QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QNotoverOperation


// QNotlessOperation
template <class T>
QNotlessOperation<T>::QNotlessOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QNotlessOperation<T>::getResult() const
{
    return this->_arg1->getResult() >= this->_arg2->getResult();
}

template <class T>
QVector <QString> QNotlessOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back(">=");

    return v;
}

template <class T>
int QNotlessOperation<T>::getDefaultPriority() const
{
    return 8;
}

template <class T>
QOperation <T> *QNotlessOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QNotlessOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QNotlessOperation<T>::getDerivative(const QString &,
                                                    QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QNotlessOperation


// QOrOperation
template <class T>
QOrOperation<T>::QOrOperation(QOperation <T> *arg1, QOperation <T> *arg2) :
    QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QOrOperation<T>::getResult() const
{
    return this->_arg1->getResult() || this->_arg2->getResult();
}

template <class T>
QVector <QString> QOrOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("|");
    v.push_back("or");
    v.push_back("Or");
    v.push_back("OR");

    return v;
}

template <class T>
int QOrOperation<T>::getDefaultPriority() const
{
    return 1;
}

template <class T>
QOperation <T> *QOrOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QOrOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QOrOperation<T>::getDerivative(const QString &,
                                               QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QOrOperation


// QXorOperation
template <class T>
QXorOperation<T>::QXorOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QXorOperation<T>::getResult() const
{
    return static_cast<bool>(this->_arg1->getResult()) ^ static_cast<bool>(this->_arg2->getResult());
}

template <class T>
QVector <QString> QXorOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("xor");
    v.push_back("Xor");
    v.push_back("XOR");

    return v;
}

template <class T>
int QXorOperation<T>::getDefaultPriority() const
{
    return 2;
}

template <class T>
QOperation <T> *QXorOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QXorOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QXorOperation<T>::getDerivative(const QString &,
                                                QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QXorOperation


// QAndOperation
template <class T>
QAndOperation<T>::QAndOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QAndOperation<T>::getResult() const
{
    return this->_arg1->getResult() && this->_arg2->getResult();
}

template <class T>
QVector <QString> QAndOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("&");
    v.push_back("and");
    v.push_back("And");
    v.push_back("AND");

    return v;
}

template <class T>
int QAndOperation<T>::getDefaultPriority() const
{
    return 3;
}

template <class T>
QOperation <T> *QAndOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QAndOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QAndOperation<T>::getDerivative(const QString &,
                                                QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QAndOperation


// QBorOperation
template <class T>
QBorOperation<T>::QBorOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QBorOperation<T>::getResult() const
{
    T res1 = this->_arg1->getResult();
    T res2 = this->_arg2->getResult();
    T result;
    uint8_t *ptr1 = (uint8_t *) &res1;
    uint8_t *ptr2 = (uint8_t *) &res2;
    uint8_t *ptr  = (uint8_t *) &result;
    for (int i = 0; i < sizeof(T); i++)
        ptr[i] = ptr1[i] | ptr2[i];

    return result;
}

template <class T>
QVector <QString> QBorOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("||");
    v.push_back("bor");
    v.push_back("Bor");
    v.push_back("BOR");

    return v;
}

template <class T>
int QBorOperation<T>::getDefaultPriority() const
{
    return 4;
}

template <class T>
QOperation <T> *QBorOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QBorOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QBorOperation<T>::getDerivative(const QString &,
                                                QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QBorOperation


// QBandOperation
template <class T>
QBandOperation<T>::QBandOperation(QOperation <T> *arg1, QOperation <T> *arg2) :
    QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QBandOperation<T>::getResult() const
{
    T res1 = this->_arg1->getResult();
    T res2 = this->_arg2->getResult();
    T result;
    uint8_t *ptr1 = (uint8_t *) &res1;
    uint8_t *ptr2 = (uint8_t *) &res2;
    uint8_t *ptr  = (uint8_t *) &result;
    for (int i = 0; i < sizeof(T); i++)
        ptr[i] = ptr1[i] & ptr2[i];

    return result;
}

template <class T>
QVector <QString> QBandOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("&&");
    v.push_back("band");
    v.push_back("Band");
    v.push_back("BAND");

    return v;
}

template <class T>
int QBandOperation<T>::getDefaultPriority() const
{
    return 6;
}

template <class T>
QOperation <T> *QBandOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QBandOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QBandOperation<T>::getDerivative(const QString &,
                                                 QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QBandOperation


// QBnotOperation
template <class T>
QBnotOperation<T>::QBnotOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QBnotOperation<T>::getResult() const
{
    T res1 = this->_arg->getResult();
    T result;
    uint8_t *ptr1 = (uint8_t *) &res1;
    uint8_t *ptr  = (uint8_t *) &result;
    for (int i = 0; i < sizeof(T); i++)
        ptr[i] = ~ptr1[i];

    return result;
}

template <class T>
QVector <QString> QBnotOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("~");
    v.push_back("bnot");
    v.push_back("Bnot");
    v.push_back("BNOT");
    v.push_back("inv");
    v.push_back("Inv");

    return v;
}

template <class T>
QOperation <T> *QBnotOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QBnotOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QBnotOperation<T>::getDerivative(const QString &,
                                                 QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QBnotOperation


// QBxorOperation
template <class T>
QBxorOperation<T>::QBxorOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QBxorOperation<T>::getResult() const
{
    T res1 = this->_arg1->getResult();
    T res2 = this->_arg2->getResult();
    T result;
    uint8_t *ptr1 = (uint8_t *) &res1;
    uint8_t *ptr2 = (uint8_t *) &res2;
    uint8_t *ptr  = (uint8_t *) &result;
    for (int i = 0; i < sizeof(T); i++)
        ptr[i] = ptr1[i] ^ ptr2[i];

    return result;
}

template <class T>
QVector <QString> QBxorOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("^^");
    v.push_back("bxor");
    v.push_back("Bxor");

    return v;
}

template <class T>
int QBxorOperation<T>::getDefaultPriority() const
{
    return 2;
}

template <class T>
QOperation <T> *QBxorOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QBxorOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QBxorOperation<T>::getDerivative(const QString &,
                                                 QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QBxorOperation


// QBlshOperation
template <class T>
QBlshOperation<T>::QBlshOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QBlshOperation<T>::getResult() const
{
    T value = this->_arg1->getResult();
    int shift = this->_arg2->getResult();
    if (sizeof(T) <= sizeof(long long)) {
        unsigned long long use = 0;
        uint8_t *valuePtr = (uint8_t *) &value;
        uint8_t *usePtr = (uint8_t *) &use;
        for (int i = 0; i < sizeof(T); i++)
            usePtr[i] = valuePtr[i];
        use <<= shift;
        for (int i = 0; i < sizeof(T); i++)
            valuePtr[i] = usePtr[i];
        return value;
    }

    return this->_arg1->getResult();
}

template <class T>
QVector <QString> QBlshOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("<<");
    v.push_back("rsh");

    return v;
}

template <class T>
int QBlshOperation<T>::getDefaultPriority() const
{
    return 9;
}

template <class T>
QOperation <T> *QBlshOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QBlshOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QBlshOperation<T>::getDerivative(const QString &,
                                                 QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QBlshOperation


// QBrshOperation
template <class T>
QBrshOperation<T>::QBrshOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QBrshOperation<T>::getResult() const
{
    T value = this->_arg1->getResult();
    int shift = this->_arg2->getResult();
    if (sizeof(T) <= sizeof(long long)) {
        unsigned long long use = 0;
        uint8_t *valuePtr = (uint8_t *) &value;
        uint8_t *usePtr = (uint8_t *) &use;
        for (int i = 0; i < sizeof(T); i++)
            usePtr[i] = valuePtr[i];
        use >>= shift;
        for (int i = 0; i < sizeof(T); i++)
            valuePtr[i] = usePtr[i];
        return value;
    }

    return this->_arg1->getResult();
}

template <class T>
QVector <QString> QBrshOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back(">>");
    v.push_back("rsh");

    return v;
}

template <class T>
int QBrshOperation<T>::getDefaultPriority() const
{
    return 9;
}

template <class T>
QOperation <T> *QBrshOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QBrshOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
            this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));
}

template <class T>
QOperation <T> *QBrshOperation<T>::getDerivative(const QString &,
                                                 QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QBrshOperation


// QSinhOperation
template <class T>
QSinhOperation<T>::QSinhOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QSinhOperation<T>::getResult() const
{
    return sinh(this->_arg->getResult());
}

template <class T>
QVector <QString> QSinhOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("sh");
    v.push_back("Sh");
    v.push_back("sinh");
    v.push_back("Sinh");

    return v;
}

template <class T>
QOperation <T> *QSinhOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QSinhOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QSinhOperation<T>::getDerivative(const QString &arg,
                                                 QFunction<T> &function) const
{
    return new QMulOperation<T>(this->_arg->getDerivative(arg, function),
                                new QCoshOperation<T>(this->_arg->getCopy()));
}
// End of QSinhOperation


// QCoshOperation
template <class T>
QCoshOperation<T>::QCoshOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QCoshOperation<T>::getResult() const
{
    return cosh(this->_arg->getResult());
}

template <class T>
QVector <QString> QCoshOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("ch");
    v.push_back("Ch");
    v.push_back("cosh");
    v.push_back("Cosh");

    return v;

}

template <class T>
QOperation <T> *QCoshOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QCoshOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QCoshOperation<T>::getDerivative(const QString &arg,
                                                 QFunction<T> &function) const
{
    return new QMulOperation<T>(this->_arg->getDerivative(arg, function),
 new QSinOperation<T>(this->_arg->getCopy()));
}
// End of QCoshOperation


// QTghOperation
template <class T>
QTghOperation<T>::QTghOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QTghOperation<T>::getResult() const
{
    return tanh(this->_arg->getResult());
}

template <class T>
QVector <QString> QTghOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("th");
    v.push_back("Th");
    v.push_back("tgh");
    v.push_back("Tgh");
    v.push_back("tanh");
    v.push_back("Tanh");

    return v;
}

template <class T>
QOperation <T> *QTghOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QTghOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QTghOperation<T>::getDerivative(const QString &arg,
                                                QFunction<T> &function) const
{
    return new QMulOperation<T>(this->_arg->getDerivative(arg, function),
 new QPowOperation<T>(new QSechOperation<T>(this->_arg->getCopy()),
 new QConstOperation<T>(2)));
}
// End of QTghOperation


// QСtghOperation
template <class T>
QCtghOperation<T>::QCtghOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QCtghOperation<T>::getResult() const
{
    return 1/tanh(this->_arg->getResult());
}

template <class T>
QVector <QString> QCtghOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("cth");
    v.push_back("Cth");
    v.push_back("ctgh");
    v.push_back("Ctgh");
    v.push_back("coth");
    v.push_back("Coth");

    return v;
}

template <class T>
QOperation <T> *QCtghOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QCtghOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QCtghOperation<T>::getDerivative(const QString &arg,
                                                 QFunction<T> &function) const
{
    return new QMulOperation<T>(this->_arg->getDerivative(arg, function),
 new QPowOperation<T>(new QCosechOperation<T>(this->_arg->getCopy()),
 new QConstOperation<T>(2)));
}
// End of QСtghOperation


// QSechOperation
template <class T>
QSechOperation<T>::QSechOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QSechOperation<T>::getResult() const
{
    return 1/cosh(this->_arg->getResult());
}

template <class T>
QVector <QString> QSechOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("sech");
    v.push_back("Sech");

    return v;
}

template <class T>
QOperation <T> *QSechOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QSechOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QSechOperation<T>::getDerivative(const QString &arg,
                                                 QFunction<T> &function) const
{
    return new QNegOperation<T>(new QMulOperation<T>(new QMulOperation<T>(this->_arg->getDerivative(arg, function),
 new QTghOperation<T>(this->_arg->getCopy())),
 new QSechOperation<T>(this->_arg->getCopy())));
}
// End of QSechOperation


// QCosechOperation
template <class T>
QCosechOperation<T>::QCosechOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QCosechOperation<T>::getResult() const
{
    return 1 / sinh(this->_arg->getResult());
}

template <class T>
QVector <QString> QCosechOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("cosech");
    v.push_back("Cosech");
    v.push_back("csch");
    v.push_back("Csch");

    return v;
}

template <class T>
QOperation <T> *QCosechOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QCosechOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QCosechOperation<T>::getDerivative(const QString &arg,
                                                   QFunction<T> &function) const
{
    return new QNegOperation<T>(new QMulOperation<T>(new QMulOperation<T>(this->_arg->getDerivative(arg, function),
 new QTghOperation<T>(this->_arg->getCopy())),
 new QSechOperation<T>(this->_arg->getCopy())));
}
// End of QCosechOperation


// QAsinhOperation
template <class T>
QAsinhOperation<T>::QAsinhOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QAsinhOperation<T>::getResult() const
{
    return asinh(this->_arg->getResult());
}

template <class T>
QVector <QString> QAsinhOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("arsh");
    v.push_back("Arsh");
    v.push_back("arcsh");
    v.push_back("Arcsh");
    v.push_back("arcsinh");
    v.push_back("Arcsinh");

    return v;
}

template <class T>
QOperation <T> *QAsinhOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QAsinhOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QAsinhOperation<T>::getDerivative(const QString &arg,
                                                  QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
 new QSqrtOperation<T>(new QSumOperation<T>(new QPowOperation<T>(this->_arg->getCopy(),
 new QConstOperation<T>(2)),
 new QConstOperation<T>(1))));
}
// End of QAsinhOperation


// QAcoshOperation
template <class T>
QAcoshOperation<T>::QAcoshOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QAcoshOperation<T>::getResult() const
{
    return acosh(this->_arg->getResult());
}

template <class T>
QVector <QString> QAcoshOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("arch");
    v.push_back("Arch");
    v.push_back("arccosh");
    v.push_back("Arccosh");

    return v;
}

template <class T>
QOperation <T> *QAcoshOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QAcoshOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QAcoshOperation<T>::getDerivative(const QString &arg,
                                                  QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
 new QSqrtOperation<T>(new QSubOperation<T>(new QPowOperation<T>(this->_arg->getCopy(),
 new QConstOperation<T>(2)),
 new QConstOperation<T>(1))));
}
// End of QAcoshOperation


// QAtghOperation
template <class T>
QAtghOperation<T>::QAtghOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QAtghOperation<T>::getResult() const
{
    return atanh(this->_arg->getResult());
}

template <class T>
QVector <QString> QAtghOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("arth");
    v.push_back("Arth");
    v.push_back("atanh");
    v.push_back("Atanh");

    return v;
}

template <class T>
QOperation <T> *QAtghOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QAtghOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QAtghOperation<T>::getDerivative(const QString &arg,
                                                 QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
 new QSubOperation<T>(new QConstOperation<T>(1),
 new QPowOperation<T>(this->_arg->getCopy(),
 new QConstOperation<T>(2))));
}
// End of QAtghOperation


// QArctghOperation
template <class T>
QArctghOperation<T>::QArctghOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QArctghOperation<T>::getResult() const
{
    return atanh(1 / this->_arg->getResult());
}

template <class T>
QVector <QString> QArctghOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("arcth");
    v.push_back("Arcth");
    v.push_back("acoth");
    v.push_back("Acoth");

    return v;
}

template <class T>
QOperation <T> *QArctghOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QArctghOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QArctghOperation<T>::getDerivative(const QString &arg,
                                                   QFunction<T> &function) const
{
    return new QDivOperation<T>(this->_arg->getDerivative(arg, function),
 new QSubOperation<T>(new QConstOperation<T>(1),
 new QPowOperation<T>(this->_arg->getCopy(),
 new QConstOperation<T>(2))));
}
// End of QArctghOperation


// QRoundOperation
template <class T>
QRoundOperation<T>::QRoundOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QRoundOperation<T>::getResult() const
{
    return qRound(this->_arg->getResult());
}

template <class T>
QVector <QString> QRoundOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("round");
    v.push_back("Round");

    return v;
}

template <class T>
QOperation <T> *QRoundOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QRoundOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QRoundOperation<T>::getDerivative(const QString &,
                                                  QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QRoundOperation


// QTruncOperation
template <class T>
QTruncOperation<T>::QTruncOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QTruncOperation<T>::getResult() const
{
    return trunc(this->_arg->getResult());
}

template <class T>
QVector <QString> QTruncOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("trunc");
    v.push_back("Trunc");

    return v;
}

template <class T>
QOperation <T> *QTruncOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QTruncOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QTruncOperation<T>::getDerivative(const QString &,
                                                  QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QTruncOperation


// QCeilOperation
template <class T>
QCeilOperation<T>::QCeilOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QCeilOperation<T>::getResult() const
{
    return ceil(this->_arg->getResult());
}

template <class T>
QVector <QString> QCeilOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("ceil");
    v.push_back("Ceil");

    return v;
}

template <class T>
QOperation <T> *QCeilOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QCeilOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QCeilOperation<T>::getDerivative(const QString &,
                                                 QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QCeilOperation


// QFractOperation
template <class T>
QFractOperation<T>::QFractOperation(QOperation <T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QFractOperation<T>::getResult() const
{
    return (double) this->_arg->getResult() - trunc(this->_arg->getResult());
}

template <class T>
QVector <QString> QFractOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("fract");
    v.push_back("Fract");

    return v;
}

template <class T>
QOperation <T> *QFractOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QFractOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QFractOperation<T>::getDerivative(const QString &,
                                                  QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QFractOperation


// QModOperation
template <class T>
QModOperation<T>::QModOperation(QOperation <T> *arg1, QOperation <T> *arg2) : QBinarOperandOperation<T>(arg1, arg2)
{
}

template <class T>
T QModOperation<T>::getResult() const
{
    return static_cast<long long>(this->_arg1->getResult()) /
            static_cast<long long>(this->_arg2->getResult());
}

template <class T>
QVector <QString> QModOperation <T>::getDefaultSynonyms() const
{
    QVector <QString> v;
    v.push_back("mod");
    v.push_back("Mod");
    v.push_back("%");

    return v;
}

template <class T>
int QModOperation<T>::getDefaultPriority() const
{
    return 11;
}

template <class T>
QOperation <T> *QModOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QModOperation<T>(this->_arg1 == nullptr ? nullptr : this->_arg1->getCopy(function),
                                this->_arg2 == nullptr ? nullptr : this->_arg2->getCopy(function));

}

template <class T>
QOperation <T> *QModOperation<T>::getDerivative(const QString &,
                                                QFunction<T> &) const
{
    return new QConstOperation<T>(0);
}
// End of QModOperation


// QConstOperation
template <class T>
QConstOperation<T>::QConstOperation(T value)
{
    _value = value;
}

template <class T>
QConstOperation<T>::~QConstOperation()
{

}

template <class T>
T QConstOperation<T>::getResult() const
{
    return _value;
}

template <class T>
QVector<QString> QConstOperation<T>::getDefaultSynonyms() const
{
    QVector<QString> v;
    v.push_back(QString::number(_value));

    return v;
}

template <class T>
QOperation <T> *QConstOperation<T>::getOperationFromString(const QString &s, int &pos,
                      const QOperationCompiler<T> &compiler) const
{
    QString name;
    QVarOperation<T> varOp;
    int pos2 = pos;
    QOperation<T> *op = varOp.getOperationFromString(s, pos2, compiler);
    T value;
    if (op != nullptr) {
        name = op->toQString(compiler);
        delete op;
        bool found = false;
        for (int i = 0; i < compiler.getLiteralConstants().length(); i++)
            if (name == compiler.getLiteralConstants()[i].getName()) {
                value = compiler.getLiteralConstants()[i].getValue();
                found = true;
                break;
            }
        if (found) {
            pos = pos2;
            if (compiler.getCompilationFlags() & CompilationFlags::LITERAL_CONSTANT_AS_VARIABLE) {
                return new QVarOperation<T>(name);
            } else {
                return new QConstOperation<T>(value);
            }
        }
    }

    int ok = 0;
    value = compiler.getValueFromString(s, pos, ok);
    if (ok < 0)
        return nullptr;
    else
        return new QConstOperation<T>(value);
}

template <class T>
int QConstOperation<T>::getDefaultPriority() const
{
    return this->CONST_OPERATION_PRIORITY;
}

template <class T>
QOperation <T> *QConstOperation<T>::getCopy() const
{
    return new QConstOperation(_value);
}

template <class T>
int QConstOperation<T>::compileFromStack(QStack<QStackUnit <T> > &)
{
    return -1;
}

template <class T>
QString QConstOperation<T>::toQString(const QOperationCompiler<T> &) const
{
    return QString::number(_value);
}

template <>
QString QConstOperation<double>::toQString(const QOperationCompiler<double> &) const
{
    return QString::number(_value, 'g', 12);
}

template <class T>
QOperation <T> *QConstOperation<T>::getCopy(QFunction<T> *) const
{
    return new QConstOperation<T>(_value);
}

template <class T>
QOperation <T> *QConstOperation<T>::getDerivative(const QString &,
                                                  QFunction<T> &) const
{
    return new QConstOperation<T>(0.0);
}

template <class T>
bool QConstOperation<T>::isAlwaysConstant() const
{
    return true;
}

template <class T>
int QConstOperation<T>::draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                             const QPoint &bottomLeft, int height, bool inBrackets) const
{
    QPainter painter;
    painter.begin(device);
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    QPoint currentPos = bottomLeft;
    QPen pen;
    QColor color = compiler.getOperationDrawingColor(this);
    pen.setColor(color);
    painter.setFont(font);
    painter.setPen(pen);
    if (inBrackets) {
        painter.drawText(currentPos, compiler.getOpeningBracket());
        currentPos.setX(currentPos.x() + fm.width(compiler.getOpeningBracket()));
    }
    painter.drawText(currentPos, toQString(compiler));
    currentPos.setX(currentPos.x() + fm.width(toQString(compiler)));
    if (inBrackets) {
        painter.drawText(currentPos, compiler.getClosingBracket());
        currentPos.setX(currentPos.x() + fm.width(compiler.getClosingBracket()));
    }
    painter.end();

    return 0;
}

template <class T>
int QConstOperation<T>::getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                        bool inBrackets) const
{
    int width = 0;
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    QTextLayout tl;
    tl.setText(toQString(compiler));
    tl.setFont(font);
    if (inBrackets)
        width += fm.boundingRect(compiler.getOpeningBracket()).width() +
                fm.boundingRect(compiler.getClosingBracket()).width();
    width += fm.boundingRect(toQString(compiler)).width();

    return width;
}
// End of QConstOperation


// QVarOperation
template <class T>
QVarOperation<T>::QVarOperation()
{
    _var = nullptr;
}

template <class T>
QVarOperation<T>::QVarOperation(const QString &name)
{
    _varName = name;
    _var = nullptr;
}

template <class T>
QVarOperation<T>::~QVarOperation()
{

}

template <class T>
T QVarOperation<T>::getResult() const
{
    return _var == nullptr ? T() : _var->_value;
}

template <class T>
QVector<QString> QVarOperation<T>::getDefaultSynonyms() const
{
    QVector<QString> v;
    v.push_back(_varName);

    return v;
}

template <class T>
int QVarOperation<T>::getDefaultPriority() const
{
    return this->CONST_OPERATION_PRIORITY;
}

template <class T>
void QVarOperation<T>::addVariablesToList(QFunction<T> &func)
{
    func.addVariable(_varName);
}

template <class T>
void QVarOperation<T>::connectVarLinks(QFunctionVariable<T> *var)
{
    if (_varName == var->_name)
        _var = var;
    else
        return;
    QVector <QFunctionVariable <T> > v = getLiteralConstantList();
    for (int i = 0; i < v.length(); i++)
        if (v[i]._name == _var->_name)
            _var->setValue(v[i]._value);
}

template <class T>
int QVarOperation<T>::compileFromStack(QStack<QStackUnit <T> > &)
{
    return -1;
}

template <class T>
QOperation <T> *QVarOperation<T>::getOperationFromString(const QString &s, int &pos,
                      const QOperationCompiler<T> &compiler) const
{
    QString varName;
    int i = pos;

    if (!compiler.isFirstVariableSymbol(s[i]))
        return nullptr;
    while (i < s.length() && compiler.isVariableSymbol(s[i])) {
        varName += s[i];
        i++;
    }
    pos = i;

    return new QVarOperation<T>(varName);
}

template <class T>
QString QVarOperation<T>::toQString(const QOperationCompiler<T>&) const
{
    return _varName;
}

template <class T>
QVector <QFunctionVariable <T> > QVarOperation<T>::getLiteralConstantList()
{
    QFunctionVariable <T> var;
    QVector <QFunctionVariable <T> > vect;
    var.setName("pi");
    var.setValue(acos(-1.0));
    vect.push_back(var);
    var.setName("e");
    var.setValue(exp(1.0));
    vect.push_back(var);

    return vect;
}

template <class T>
QOperation <T> *QVarOperation<T>::getCopy() const
{
    QVarOperation<T> *op = new QVarOperation<T>;
    op->_varName = _varName;
    op->_var = _var;
    return op;
}

template <class T>
QOperation <T> *QVarOperation<T>::getDerivative(const QString &argName,
                                                QFunction<T> &) const
{
    if (argName == _var->_name)
        return new QConstOperation<T>(1.0);
    else
        return new QConstOperation<T>(0.0);
}

template <class T>
bool QVarOperation<T>::isAlwaysConstant() const
{
    return false;
}

template <class T>
int QVarOperation<T>::draw(QPaintDevice *device, const QOperationCompiler<T> &compiler,
                           const QPoint &bottomLeft, int height, bool inBrackets) const
{
    double ratio = 0.3;
    QString s = toQString(compiler);
    QPainter painter;
    painter.begin(device);
    painter.setRenderHints(QPainter::Antialiasing);
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    QPoint currentPos = bottomLeft;
    QPen pen;
    QColor color = compiler.getOperationDrawingColor(this);
    pen.setColor(color);
    painter.setPen(pen);
    painter.setFont(font);
    int i = 0;
    QString s1, s2;
    for (i = 0; i < s.length() && s[i] != QChar('_'); i++)
        s1 += s[i];
    i++;
    for (; i < s.length(); i++)
        s2 += s[i];
    if (inBrackets) {
        painter.drawText(currentPos, compiler.getOpeningBracket());
        currentPos.setX(currentPos.x() + fm.width(compiler.getOpeningBracket()));
    }
    painter.drawText(currentPos, s1);
    currentPos.setX(currentPos.x() + fm.width(s1));
    font.setPixelSize((int) qRound((double) height * ratio));
    painter.setFont(font);
    painter.drawText(currentPos, s2);
    currentPos.setX(currentPos.x() + (int) qRound((double) fm.width(s2) * ratio));
    if (inBrackets)
        painter.drawText(currentPos, compiler.getClosingBracket());
    painter.end();

    return 0;
}

template <class T>
int QVarOperation<T>::getDrawingWidth(const QOperationCompiler<T> &compiler, int height,
                                      bool inBrackets) const
{
    double ratio = 0.3;
    int width = 0;
    QString s = toQString(compiler);
    QFont font = compiler.getDrawingFont();
    font.setPixelSize(height);
    QFontMetrics fm(font);
    if (inBrackets)
        width += fm.width(compiler.getOpeningBracket()) + fm.width(compiler.getClosingBracket());
    QString s1, s2;
    int i = 0;
    for (i = 0; i < s.length() && s[i] != QChar('_'); i++)
        s1 += s[i];
    i++;
    for (; i < s.length(); i++)
        s2 += s[i];
    width += fm.width(s1);
    width += (int) qRound((double) fm.width(s2) * ratio);

    return width;
}
// End of QVarOperation


// QNegOperation
template <class T>
QNegOperation<T>::QNegOperation(QOperation<T> *arg) : QUnarPrefixOperation<T>(arg)
{
}

template <class T>
T QNegOperation<T>::getResult() const
{
    return - this->_arg->getResult();
}

template <class T>
QOperation<T> *QNegOperation<T>::getOperationFromString(const QString &s, int &pos,
                                                        const QOperationCompiler<T> &) const
{
    for (int j = 0; j < getDefaultSynonyms().length(); j++) {
        QString synonym = getDefaultSynonyms()[j];
        int i;

        for (i = 0; i + pos < s.length() && i < synonym.length() ; i++) {
            if (s[i + pos] != synonym[i])
                break;
        }

        if (i == synonym.length()) {
            if (pos == 0 || (pos > 0 && !QOperation<T>::isClosingBracket(s[pos - 1]) &&
                             !s[pos - 1].isDigit() && !s[pos - 1].isLetter())) {
                pos += i;
                return new QNegOperation<T>(nullptr);
            }
        }
    }

    return nullptr;
}

template <class T>
bool QNegOperation<T>::operationStartsHere(const QString &s, int pos, QFunction <T> &,
                                           const QOperationCompiler <T> &) const
{
    for (int j = 0; j < getDefaultSynonyms().length(); j++) {
        QString synonym = getDefaultSynonyms()[j];
        int i;

        for (i = 0; i + pos < s.length() && i < synonym.length() ; i++) {
            if (s[i + pos] != synonym[i])
                break;
        }

        if (i == synonym.length()) {
            if (pos == 0 || (pos > 0 && !QOperation<T>::isClosingBracket(s[pos - 1]) &&
                             !s[pos - 1].isDigit() && !s[pos - 1].isLetter())) {
                return true;
            }
        }
    }

    return false;
}

template <class T>
QOperation <T> *QNegOperation<T>::getCopy(QFunction<T> *function) const
{
    return new QNegOperation<T>(this->_arg == nullptr ? nullptr : this->_arg->getCopy(function));
}

template <class T>
QOperation <T> *QNegOperation<T>::getDerivative(const QString &argName,
                                                QFunction<T> &parentFunction) const
{
    return new QNegOperation(this->_arg->getDerivative(argName, parentFunction));
}

template <class T>
void QNegOperation<T>::makeSumPolynomial(QVector<QOperation<T> *> &positive,
                                         QVector<QOperation<T> *> &negative)
{
    this->_arg->makeSumPolynomial(negative, positive);
}

template <class T>
QVector<QString> QNegOperation<T>::getDefaultSynonyms() const
{
    QVector<QString> v;
    v.push_back("-");

    return v;
}
// End of QNegOperation


// Typedefs
typedef QFunction<double>    QDoubleFunction;
typedef QFunction<int>       QIntFunction;
typedef QFunction<long long> QLongLongFunction;
typedef QFunction<bool>      QBoolFunction;

typedef QOperationCompiler<double>    QDoubleCompiler;
typedef QOperationCompiler<int>       QIntCompiler;
typedef QOperationCompiler<long long> QLongLongCompiler;
typedef QOperationCompiler<bool>      QBoolCompiler;
// End of typedefs

} // End of namespace.


#endif // QOPERATION_H

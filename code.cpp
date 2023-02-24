# include <stdio.h>
# include <string>    // string, find_last_of, substr
# include <cstring>   // strcpy
# include <vector>    // vector, push_back
# include <stdlib.h>
# include <cstdlib>   // system, atoi
# include <cctype>    // isalpha
# include <map>
# include <sstream>   // type conversion
# include <iostream>  // cout, endl

using namespace std ;

# define MAX 80

enum GrammerType
{
  IDENT, INT, FLOAT, CHAR, STRING, BOOL, OP, NON
} ;

enum ErrorType
{
  SCANNER_ERROR, PARSER_ERROR, EVALUATOR_ERROR
} ;

enum EvalType
{
  LIST_ALL_VAR, LIST_ALL_FUNC, LIST_VAR, LIST_FUNC, DONE, EXEC
} ;

struct LabelOfToken
{
  string array_size ;
  string tokenValue ;
  GrammerType tokenType ;
} ;

struct LabelOfVar
{
  int indexOfVarName ;
  int timesOfArray ;
} ;

// this boolean means that the scanner is correct or not
bool gScannerCorrect ;
// the input is the function declaration now
bool gInputNowIsFunc ;
// no need to print the message when it is a complete set of inputs
bool gASetOfInput ;
// currently input is declaring variable
bool gVarDeclar ;
// currently input is the declaration function
bool gFuncDeclar ;
// used to determine whether a declared variable or function has been found
bool gNoDefinedValue ;
// [x] x's number can't be negative
bool gNumOfArrayIsError ;
// ; is one of the end of input
bool gTheEndOfInput ;
// clean up the white space after the input
bool gCleanWhiteSpaceAfterInput ;
// used to determine whether to stop executing the program
bool gQuit ;
// used to calculate the number of current instruction lines
int gCurrentLine ;

// this is an intermediate station for PeekToken() and GetToken()
LabelOfToken gTempToken ; 
// this means the current get token
LabelOfToken gCurrentToken ;
// this means the error token in parser
string gUnexpectedToken ;

// save a long list of tokens
vector<LabelOfToken> gTokenList ;
// used to store var index
vector<LabelOfVar> gIndexOfDefinedVar ;
// used to save the function's parameter
vector <string> gFuncParameters ;
// used to store all declared variable names
vector<string> gAllOfVarName ;
// Used to store all declared function names
vector<string> gAllOfFuncName ;
// used to store the declared variables
map<string, LabelOfToken> gMapVar ;
// used to store the regional variables
map<string, LabelOfToken> gMapLocalVar ;
// used to store the declared functions
map<string, vector<string> > gMapFunc ;

// ------------------functions for all----------------------------
void PrintErrorMessage( ErrorType errorType, string erroneous ) ;
void SkipWhiteSpace() ;
void SkipComment() ;
// ---------------------------------------------------------------

// ------------------functions used by Scanner-------------------- 
bool PeekToken( LabelOfToken& peekToken ) ;
void GetToken( LabelOfToken& getToken ) ;
void ScannerCase( char firstCh, GrammerType& tokenType ) ;
bool Scanner() ;
// ---------------------------------------------------------------

// ------------------functions used by Parser---------------------
void Unsigned_Unary_Exp( bool& unsignedUnaryExpCorrect ) ;
void Signed_Unary_Exp( bool& signedUnaryExpCorrect ) ;
void Unary_Exp( bool& UnaryExpCorrect ) ;
void Rest_Of_Maybe_Mult_Exp( bool& restOfMaybeMultExpCorrect ) ;
void Maybe_Mult_Exp( bool& maybeMultExpCorrect ) ;
void Rest_Of_Maybe_Additive_Exp( bool& restOfMaybeAdditExpCorrect ) ;
void Maybe_Additive_Exp( bool& maybeAdditExpCorrect ) ;
void Rest_Of_Maybe_Shift_Exp( bool& restOfMaybeShiftExpCorrect ) ;
void Maybe_Shift_Exp( bool& maybeShiftExpCorrect ) ;
void Rest_Of_Maybe_Relational_Exp( bool& restOfMaybeRelationalExpCorrect ) ;
void Maybe_Relational_Exp( bool& maybeRelationalExpCorrect ) ;
void Rest_Of_Maybe_Equality_Exp( bool& restOfMaybeEqualExpCorrect ) ;
void Maybe_Equality_Exp( bool& maybeEqualExpCorrect ) ;
void Rest_Of_Maybe_Bit_AND_Exp( bool& restOfMaybeBitANDExpCorrect ) ;
void Maybe_Bit_AND_Exp( bool& maybeBitANDExpCorrect ) ;
void Rest_Of_Maybe_Bit_Ex_OR_Exp( bool& restOfMaybeBitExORExpCorrect ) ;
void Maybe_Bit_Ex_OR_Exp( bool& maybeBitExORExpCorrect ) ;
void Rest_Of_Maybe_Bit_OR_Exp( bool& restOfMaybeBitORExpCorrect ) ;
void Maybe_Bit_OR_Exp( bool& maybeBitORExpCorrect ) ;
void Rest_Of_Maybe_Logical_AND_Exp( bool& restOfMaybeLogicalANDExpCorrect ) ;
void Maybe_Logical_AND_Exp( bool& maybeLogicalANDExpCorrect ) ;
void Rest_Of_Maybe_Logical_OR_Exp( bool& restOfMaybeLogicalORExpCorrect ) ;
void Romce_And_Romloe( bool& romceAndRomloeCorrect ) ;
void Assignment_Operator( bool& asgmtOprCorrect ) ;
void Actual_Parameter_List( bool& actualPrmListCorrect ) ;
void Sign( bool& signCorrect ) ;
void Rest_Of_PPMM_ID_Started_Basic_Exp( bool& restOfPPMMIDStartedBasicExpCorrect ) ;
void Rest_Of_ID_Started_Basic_Exp( bool& restOfIDStartedBasicExpCorrect ) ;
void Basic_Expression( bool& basicExprCorrect ) ;
void Expression( bool& exprCorrect ) ;
void Statement( bool& stmtCorrect ) ;
void Declaration( bool& dclCorrect ) ;
void Compound_Statement( bool& compoundStmtCorrect ) ;
void Formal_Parameter_List( bool& formalPrmListCorrect ) ;
void Function_Definition_Without_ID( bool& funDefWithoutIDCorrect ) ;
void Rest_Of_Declarators( bool& restOfDclCorrect ) ;
void Function_Definition_Or_Declarators( bool& funDefOrDclCorrect ) ;
void Type_Specifier( bool& typeSpeciCorrect ) ;
void Definition( bool& defCorrect ) ;
void User_Input( bool& userInputCorrect ) ;
bool FindDefinedValue( string definedVal ) ;
bool Parser() ;
// ---------------------------------------------------------------

// ------------------functions used by Evaluator------------------
void SetDefinedLocalVarForParameter() ;
void SetDefinedLocalVar() ;
void SetDefinedVar() ;
void SetDefinedFunc() ;
void DealWithEXEC() ;
bool GrabParm( string& parameter ) ;
void BubbleSort( vector<string>& vectorOfDef ) ;
EvalType ClassForEvalType( string& parameter ) ;
void Evaluator() ;
void EXECmd() ;
void InToPoAndRepDef(  vector<string>& postfixTokenList, 
                       vector<LabelOfToken>& infixTokenList ) ;
int PriForCal( string op ) ;
string CalPostfixVal( vector<string>& postfixTokenList ) ;
bool IsString( string str ) ;
bool HaveEnter( string str ) ;
string CalTwoOp( string op, string strLeft, string strRight ) ;
string ComprTwoOp( string op, string strLeft, string strRight ) ;
string BoolTwoOp( string op, string strLeft, string strRight ) ;
string EvalTwoOp( string op, string strLeft, string strRight ) ;
string AssignValue( string op, string strLeft, string strRight ) ;
string DealWithSign( string op, string value ) ;
void ReorganizeTokenList( vector<LabelOfToken>& tempTokenList ) ;
string DealWithCondition( int& i, vector<string>& postfixTokenList, string boolOfEXE ) ;
void AddConEndOP( vector<LabelOfToken>& splitTokenList ) ;
// ---------------------------------------------------------------

int main()
{
  gQuit = false ;

  cout << "Our-C running ..." << endl ;
  
  while ( !gQuit )
  {
    cout << "> " ;

    if ( Parser() && !gQuit )
      Evaluator() ;

    // gTempToken.tokenValue = "" ;
    gTokenList.clear() ;
    gIndexOfDefinedVar.clear() ;
    gIndexOfDefinedVar.clear() ;
  } // while

  gMapVar.clear() ;
  gMapFunc.clear() ;
  gAllOfVarName.clear() ;
  gAllOfFuncName.clear() ;

  cout << "Our-C exited ..." << endl ;
} // main()

void PrintErrorMessage( ErrorType errorType, string erroneous ) 
// use ErrorType to print the error message
{
  // it's lexical error (error on the token level)
  if ( errorType == SCANNER_ERROR ) 
    cout << "Line " << gCurrentLine << " : "
         << "unrecognized token with first char : " 
         << "'" << erroneous << "'" << endl ; 
  // it's syntactic(syntax) error (token recognized)
  else if ( errorType == PARSER_ERROR ) 
    cout << "Line " << gCurrentLine << " : "
         << "unexpected token : " << "'" << erroneous << "'" << endl ;
  else if ( errorType == EVALUATOR_ERROR ) // (grammar OK)
    cout << "Line " << gCurrentLine << " : " 
         << "undefined identifier : " << "'" << erroneous << "'" << endl ;

  gTempToken.tokenValue = "" ;
  gUnexpectedToken = "" ;
  gTokenList.clear() ;
  SkipComment() ;
} // PrintErrorMessage()

void SkipWhiteSpace()
{
  if ( gCleanWhiteSpaceAfterInput )
  {
    while ( cin.peek() == ' ' || cin.peek() == '\t' )
      cin.get() ; 
  } // if
  else
  {
    while ( cin.peek() == ' ' || cin.peek() == '\t' || cin.peek() == '\n' )
    {
      if ( cin.peek() == '\n' )
        gCurrentLine++ ;
      cin.get() ; 
    } // while
  } // else
} // SkipWhiteSpace()

void SkipComment()
// read until new line
{
  char ch = '\0' ;
  while ( cin.peek() != '\n' )
    cin.get() ;  
  ch = cin.get() ; // read '\n'
  gCurrentLine++ ;
} // SkipComment()

bool PeekToken( LabelOfToken& peekToken ) 
// peek a token (but that doesn't mean we won't take it out)
// return false means that we read the invalid character (SCANNER_ERROR)
{
  char ch = '\0' ;
  peekToken.tokenValue = "" ;
  peekToken.tokenType = NON ;

  SkipWhiteSpace() ; 
  ch = cin.get() ; // get the first char
 
  if ( ch == '\n' && gCleanWhiteSpaceAfterInput )
    return false ;

  peekToken.tokenValue = ch ;

  // deal with comment
  while ( peekToken.tokenValue == "/" && cin.peek() == '/' ) 
  {
    SkipComment() ; // read until new line

    if ( !gCleanWhiteSpaceAfterInput )
    {
      SkipWhiteSpace() ; 
      ch = cin.get() ; // read a new line of new char
      peekToken.tokenValue = ch ;
    } // if
    else
    {
      peekToken.tokenValue = "" ;
      return false ;
    } // else
  } // while

  // use the token's first char to allocate the tokenType
  ScannerCase( ch, peekToken.tokenType ) ;

  if ( ch == EOF )
  {
    gQuit = true ;
    return true ;
  } // if
  else if ( ch == ';' || ch == ',' )
    return true ;
  else if ( ch == '?' || ch == ':' )
  {
    peekToken.tokenType = OP ;
    return true ;
  } // else if
  else if ( ch == '(' || ch == ')' || ch == '[' || ch == ']' || 
            ch == '{' || ch == '}' )
    return true ;
  else if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' || 
            ch == '%' || ch == '^' )
  {
    if ( ( ch == '+' && cin.peek() == '=' ) ||
         ( ch == '-' && cin.peek() == '=' ) ||
         ( ch == '*' && cin.peek() == '=' ) ||
         ( ch == '/' && cin.peek() == '=' ) ||
         ( ch == '%' && cin.peek() == '=' ) ||
         ( ch == '+' && cin.peek() == '+' ) ||
         ( ch == '-' && cin.peek() == '-' ) )
    {
      ch = cin.get() ;
      peekToken.tokenValue = peekToken.tokenValue + ch ;
    } // if

    peekToken.tokenType = OP ;
    return true ;
  } // else if
  else if ( ch == '>' || ch == '<' || ch == '=' || ch == '&' || 
            ch == '|' || ch == '!' )
  {
    if ( ( ch == '=' && cin.peek() == '=' ) ||
         ( ch == '<' && cin.peek() == '=' ) ||
         ( ch == '>' && cin.peek() == '=' ) ||
         ( ch == '!' && cin.peek() == '=' ) ||
         ( ch == '>' && cin.peek() == '>' ) ||
         ( ch == '<' && cin.peek() == '<' ) ||
         ( ch == '&' && cin.peek() == '&' ) || 
         ( ch == '|' && cin.peek() == '|' ) )
    {
      ch = cin.get() ;
      peekToken.tokenValue = peekToken.tokenValue + ch ;
    } // if

    peekToken.tokenType = OP ;
    return true ;
  } // else if
  else if ( peekToken.tokenType == IDENT )
  {
    while ( isalpha( cin.peek() ) || cin.peek() == '_' || isdigit( cin.peek() ) ) 
    { // combined complete IDENT
      ch = cin.get() ;
      peekToken.tokenValue = peekToken.tokenValue + ch ;
    } // while
    
    if ( peekToken.tokenValue == "true" || peekToken.tokenValue == "false" )
      peekToken.tokenType = BOOL ;
    else if ( peekToken.tokenValue == "int"    || peekToken.tokenValue == "float" ||
              peekToken.tokenValue == "char"   || peekToken.tokenValue == "bool"  || 
              peekToken.tokenValue == "string" || peekToken.tokenValue == "void"  ||
              peekToken.tokenValue == "if"     || peekToken.tokenValue == "else"  ||
              peekToken.tokenValue == "while"  || peekToken.tokenValue == "do"    ||
              peekToken.tokenValue == "return" )
      peekToken.tokenType = NON ;

    return true ;
  } // else if
  else if ( peekToken.tokenType == INT || peekToken.tokenType == FLOAT )
  {
    while ( isdigit( cin.peek() ) || cin.peek() == '.' )
    {
      if ( peekToken.tokenType == FLOAT && cin.peek() == '.' )
        return true ;

      ch = cin.get() ;
      peekToken.tokenValue = peekToken.tokenValue + ch ;

      if ( ch == '.' )
        peekToken.tokenType = FLOAT ;
    } // while
    
    if ( peekToken.tokenValue == "." ) // just a point is error
      return false ;

    return true ;
  } // else if
  else if ( peekToken.tokenType == CHAR )
  {
    while ( cin.peek() != '\'' )
    {
      ch = cin.get() ;
      peekToken.tokenValue = peekToken.tokenValue + ch ;
    } // while

    ch = cin.get() ; // '
    peekToken.tokenValue = peekToken.tokenValue + ch ;
    return true ;
  } // else if
  else if ( peekToken.tokenType == STRING )
  {
    while ( cin.peek() != '\"' )
    {
      ch = cin.get() ;
      peekToken.tokenValue = peekToken.tokenValue + ch ;
    } // while

    ch = cin.get() ; // "
    peekToken.tokenValue = peekToken.tokenValue + ch ;
    return true ;
  } // else if
  else
    return false ;
} // PeekToken()

void GetToken( LabelOfToken& getToken )
// when it conforms to the grammer, it can be retrieved through Scanner()
// when the tempToken is taken out, let the Scanner() take the next one and wait
// when it doesn't conform to the grammer, keep the current tempToken value
{
  getToken.tokenValue = gTempToken.tokenValue ;
  getToken.tokenType = gTempToken.tokenType ;
  gTokenList.push_back( getToken ) ;
  gTempToken.tokenValue = "" ;
  gTempToken.tokenType = NON ;
} // GetToken()

void ScannerCase( char firstCh, GrammerType& tokenType )
// use the token's first char to allocate its case
{
  if ( isalpha( firstCh ) != 0 ) // IDENT
    tokenType = IDENT ;
  else if ( isdigit( firstCh ) != 0 ) // INT
    tokenType = INT ;
  else if ( firstCh == '.' ) // FLOAT
    tokenType = FLOAT ;
  else if ( firstCh == '\'' ) // CHAR
    tokenType = CHAR ;
  else if ( firstCh == '\"' ) // STRING
    tokenType = STRING ;
  else
    tokenType = NON ;
} // ScannerCase()

bool Scanner()
// if scanner error, output error message and return false
{
  bool isToken = true ;

  if ( gTempToken.tokenValue.empty() )
  {
    isToken = PeekToken( gTempToken ) ;
    if ( !isToken ) // scanner error
    {
      gScannerCorrect = false ;
      PrintErrorMessage( SCANNER_ERROR, gTempToken.tokenValue ) ;
      return false ;
    } // if
    else if ( gQuit )
      return false ;
  } // if

  return true ;
} // Scanner()

void Unsigned_Unary_Exp( bool& unsignedUnaryExpCorrect )
// unsigned_unary_exp
//     : Identifier [ '(' [ actual_parameter_list ] ')' 
//                    |
//                    [ '[' expression ']' ] [ ( PP | MM ) ]
//                  ]
//     | Constant 
//     | '(' expression ')'
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenType == IDENT )
  {
    if ( !FindDefinedValue( gTempToken.tokenValue ) )
    {
      gNoDefinedValue = true ;
      return ;
    } // if

    GetToken( gCurrentToken ) ;

    unsignedUnaryExpCorrect = true ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenValue == "(" )
    {
      GetToken( gCurrentToken ) ;

      bool actualPrmListCorrect = false ;
      Actual_Parameter_List( actualPrmListCorrect ) ;

      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == ")" )
        GetToken( gCurrentToken ) ;
      else
      {
        unsignedUnaryExpCorrect = false ;
        gUnexpectedToken = gTempToken.tokenValue ;
      } // else
    } // if
    else 
    {
      if ( gTempToken.tokenValue == "[" )
      {
        GetToken( gCurrentToken ) ;

        bool exprCorrect = false ;
        Expression( exprCorrect ) ;

        if ( exprCorrect )
        {
          if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
            return ;

          if ( gTempToken.tokenValue == "]" )
            GetToken( gCurrentToken ) ;
          else
          {
            unsignedUnaryExpCorrect = false ;
            gUnexpectedToken = gTempToken.tokenValue ;
            return ;
          } // else
        } // if
        else
        {
          unsignedUnaryExpCorrect = false ;
          return ;
        } // else
      } // if
      
      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == "++" || gTempToken.tokenValue == "--" )
        GetToken( gCurrentToken ) ;
    } // else
  } // if
  else if ( gTempToken.tokenType == INT  || gTempToken.tokenType == FLOAT  ||
            gTempToken.tokenType == CHAR || gTempToken.tokenType == STRING ||
            gTempToken.tokenType == BOOL ) // Constant
  {
    GetToken( gCurrentToken ) ;

    unsignedUnaryExpCorrect = true ;
  } // else if
  else if ( gTempToken.tokenValue == "(" )
  {
    GetToken( gCurrentToken ) ;

    bool exprCorrect = false ;
    Expression( exprCorrect ) ;

    if ( exprCorrect )
    {
      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == ")" )
      {
        GetToken( gCurrentToken ) ;

        unsignedUnaryExpCorrect = true ;
      } // if
      else
        gUnexpectedToken = gTempToken.tokenValue ;
    } // if
  } // else if
  else
    gUnexpectedToken = gTempToken.tokenValue ;
} // Unsigned_Unary_Exp()

void Signed_Unary_Exp( bool& signedUnaryExpCorrect )
// signed_unary_exp
//     : Identifier [ '(' [ actual_parameter_list ] ')' 
//                    |
//                    '[' expression ']'
//                  ]
//     | Constant 
//     | '(' expression ')'
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenType == IDENT )
  {
    if ( !FindDefinedValue( gTempToken.tokenValue ) )
    {
      gNoDefinedValue = true ;
      return ;
    } // if

    GetToken( gCurrentToken ) ;

    signedUnaryExpCorrect = true ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenValue == "(" )
    {
      GetToken( gCurrentToken ) ;

      bool actualPrmListCorrect = false ;
      Actual_Parameter_List( actualPrmListCorrect ) ;

      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == ")" )
        GetToken( gCurrentToken ) ;
      else
      {
        signedUnaryExpCorrect = false ;
        gUnexpectedToken = gTempToken.tokenValue ;
      } // else
    } // if
    else if ( gTempToken.tokenValue == "[" )
    {
      GetToken( gCurrentToken ) ;

      bool exprCorrect = false ;
      Expression( exprCorrect ) ;

      if ( exprCorrect )
      {
        if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
          return ;

        if ( gTempToken.tokenValue == "]" )
          GetToken( gCurrentToken ) ;
        else
        {
          signedUnaryExpCorrect = false ;
          gUnexpectedToken = gTempToken.tokenValue ;
        } // else
      } // if
      else
        signedUnaryExpCorrect = false ;
    } // else if
  } // if
  else if ( gTempToken.tokenType == INT  || gTempToken.tokenType == FLOAT  ||
            gTempToken.tokenType == CHAR || gTempToken.tokenType == STRING ||
            gTempToken.tokenType == BOOL ) // Constant
  {
    GetToken( gCurrentToken ) ;

    signedUnaryExpCorrect = true ;
  } // else if
  else if ( gTempToken.tokenValue == "(" )
  {
    GetToken( gCurrentToken ) ;

    bool exprCorrect = false ;
    Expression( exprCorrect ) ;

    if ( exprCorrect )
    {
      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == ")" )
      {
        GetToken( gCurrentToken ) ;

        signedUnaryExpCorrect = true ;
      } // if
      else
        gUnexpectedToken = gTempToken.tokenValue ;
    } // if
  } // else if
  else
    gUnexpectedToken = gTempToken.tokenValue ;
} // Signed_Unary_Exp()

void Unary_Exp( bool& UnaryExpCorrect )
// unary_exp
//     : sign { sign } signed_unary_exp
//     | unsigned_unary_exp
//     | ( PP | MM ) Identifier [ '[' expression ']' ]
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenValue == "++" || gTempToken.tokenValue == "--" )
  {
    GetToken( gCurrentToken ) ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenType == IDENT )
    {
      if ( !FindDefinedValue( gTempToken.tokenValue ) )
      {
        gNoDefinedValue = true ;
        return ;
      } // if

      GetToken( gCurrentToken ) ;

      UnaryExpCorrect = true ;

      if ( gTempToken.tokenValue == "[" )
      {
        GetToken( gCurrentToken ) ;

        bool exprCorrect = false ;
        Expression( exprCorrect ) ;

        if ( exprCorrect )
        {
          if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
            return ;

          if ( gTempToken.tokenValue == "]" )
            GetToken( gCurrentToken ) ;
          else
          {
            UnaryExpCorrect = false ;
            gUnexpectedToken = gTempToken.tokenValue ;
          } // else
        } // if
        else
          UnaryExpCorrect = false ;
      } // if
    } // if
    else
      gUnexpectedToken = gTempToken.tokenValue ;
  } // if
  else
  {
    bool signOneCorrect = false ;
    Sign( signOneCorrect ) ;

    if ( signOneCorrect )
    {
      bool signTwoCorrect = true ;
      
      while ( signTwoCorrect )
      {
        signTwoCorrect = false ;
        Sign( signTwoCorrect ) ;
      } // while

      bool signedUnaryExpCorrect = false ;
      Signed_Unary_Exp( signedUnaryExpCorrect ) ;

      if ( signedUnaryExpCorrect )
        UnaryExpCorrect = true ;
    } // if
    else
    {
      bool unsignedUnaryExpCorrect = false ;
      Unsigned_Unary_Exp( unsignedUnaryExpCorrect ) ;

      if ( unsignedUnaryExpCorrect )
        UnaryExpCorrect = true ;
    } // else
  } // else
} // Unary_Exp()

void Rest_Of_Maybe_Mult_Exp( bool& restOfMaybeMultExpCorrect )
// rest_of_maybe_mult_exp 
//     : { ( '*' | '/' | '%' ) unary_exp }  /* could be empty ! */
{
  restOfMaybeMultExpCorrect = true ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "*" || gTempToken.tokenValue == "/" ||
          gTempToken.tokenValue == "%" )
  {
    GetToken( gCurrentToken ) ;

    bool unaryExpCorrect = false ;
    Unary_Exp( unaryExpCorrect ) ;

    if ( !unaryExpCorrect )
    {
      restOfMaybeMultExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while
} // Rest_Of_Maybe_Mult_Exp()

void Maybe_Mult_Exp( bool& maybeMultExpCorrect )
// maybe_mult_exp 
//     : unary_exp rest_of_maybe_mult_exp
{
  bool unaryExpCorrect = false ;
  Unary_Exp( unaryExpCorrect ) ;

  if ( unaryExpCorrect )
  {
    bool restOfMaybeMultExpCorrect = false ;
    Rest_Of_Maybe_Mult_Exp( restOfMaybeMultExpCorrect ) ;

    if ( restOfMaybeMultExpCorrect )
      maybeMultExpCorrect = true ;
  } // if
} // Maybe_Mult_Exp()

void Rest_Of_Maybe_Additive_Exp( bool& restOfMaybeAdditExpCorrect )
// rest_of_maybe_additive_exp 
//     : rest_of_maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
{
  bool restOfMaybeMultExpCorrect = false ;
  Rest_Of_Maybe_Mult_Exp( restOfMaybeMultExpCorrect ) ;

  if ( restOfMaybeMultExpCorrect )
    restOfMaybeAdditExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "+"  || gTempToken.tokenValue == "-" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeMultExpCorrect = false ;
    Maybe_Mult_Exp( maybeMultExpCorrect ) ;

    if ( !maybeMultExpCorrect )
    {
      restOfMaybeAdditExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Rest_Of_Maybe_Additive_Exp()

void Maybe_Additive_Exp( bool& maybeAdditExpCorrect )
// maybe_additive_exp 
//     : maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
{
  bool maybeMultExpOneCorrect = false ;
  Maybe_Mult_Exp( maybeMultExpOneCorrect ) ;

  if ( maybeMultExpOneCorrect )
    maybeAdditExpCorrect = true ;
  else 
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "+"  || gTempToken.tokenValue == "-" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeMultExpTwoCorrect = false ;
    Maybe_Mult_Exp( maybeMultExpTwoCorrect ) ;

    if ( !maybeMultExpTwoCorrect )
    {
      maybeAdditExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Maybe_Additive_Exp()

void Rest_Of_Maybe_Shift_Exp( bool& restOfMaybeShiftExpCorrect )
// rest_of_maybe_shift_exp 
//     : rest_of_maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
{
  bool restOfMaybeAdditExpCorrect = false ;
  Rest_Of_Maybe_Additive_Exp( restOfMaybeAdditExpCorrect ) ;

  if ( restOfMaybeAdditExpCorrect )
    restOfMaybeShiftExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "<<"  || gTempToken.tokenValue == ">>" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeAdditExpCorrect = false ;
    Maybe_Additive_Exp( maybeAdditExpCorrect ) ;

    if ( !maybeAdditExpCorrect )
    {
      restOfMaybeShiftExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Rest_Of_Maybe_Shift_Exp()

void Maybe_Shift_Exp( bool& maybeShiftExpCorrect )
// maybe_shift_exp 
//     : maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
{
  bool maybeAdditExpOneCorrect = false ;
  Maybe_Additive_Exp( maybeAdditExpOneCorrect ) ;

  if ( maybeAdditExpOneCorrect )
    maybeShiftExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "<<"  || gTempToken.tokenValue == ">>" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeAdditExpTwoCorrect = false ;
    Maybe_Additive_Exp( maybeAdditExpTwoCorrect ) ;

    if ( !maybeAdditExpTwoCorrect )
    {
      maybeShiftExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Maybe_Shift_Exp()

void Rest_Of_Maybe_Relational_Exp( bool& restOfMaybeRelationalExpCorrect )
// rest_of_maybe_relational_exp 
//     : rest_of_maybe_shift_exp 
//       { ( '<' | '>' | LE | GE ) maybe_shift_exp }
{
  bool restOfMaybeShiftExpCorrect = false ;
  Rest_Of_Maybe_Shift_Exp( restOfMaybeShiftExpCorrect ) ;

  if ( restOfMaybeShiftExpCorrect )
    restOfMaybeRelationalExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "<"  || gTempToken.tokenValue == ">" ||
          gTempToken.tokenValue == "<=" || gTempToken.tokenValue == ">=" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeShiftExpCorrect = false ;
    Maybe_Shift_Exp( maybeShiftExpCorrect ) ;

    if ( !maybeShiftExpCorrect )
    {
      restOfMaybeRelationalExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Rest_Of_Maybe_Relational_Exp()

void Maybe_Relational_Exp( bool& maybeRelationalExpCorrect )
// maybe_relational_exp 
//     : maybe_shift_exp 
//       { ( '<' | '>' | LE | GE ) maybe_shift_exp }
{
  bool maybeShiftExpOneCorrect = false ;
  Maybe_Shift_Exp( maybeShiftExpOneCorrect ) ;

  if ( maybeShiftExpOneCorrect )
    maybeRelationalExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "<"  || gTempToken.tokenValue == ">" ||
          gTempToken.tokenValue == "<=" || gTempToken.tokenValue == ">=" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeShiftExpTwoCorrect = false ;
    Maybe_Shift_Exp( maybeShiftExpTwoCorrect ) ;

    if ( !maybeShiftExpTwoCorrect )
    {
      maybeRelationalExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Maybe_Relational_Exp()

void Rest_Of_Maybe_Equality_Exp( bool& restOfMaybeEqualExpCorrect )
// rest_of_maybe_equality_exp 
//     : rest_of_maybe_relational_exp 
//       { ( EQ | NEQ ) maybe_relational_exp }
{
  bool restOfMaybeRelationalExpCorrect = false ;
  Rest_Of_Maybe_Relational_Exp( restOfMaybeRelationalExpCorrect ) ;

  if ( restOfMaybeRelationalExpCorrect )
    restOfMaybeEqualExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "==" || gTempToken.tokenValue == "!=" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeRelationalExpCorrect = false ;
    Maybe_Relational_Exp( maybeRelationalExpCorrect ) ;

    if ( !maybeRelationalExpCorrect )
    {
      restOfMaybeEqualExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Rest_Of_Maybe_Equality_Exp()

void Maybe_Equality_Exp( bool& maybeEqualExpCorrect )
// maybe_equality_exp 
//     : maybe_relational_exp 
//       { ( EQ | NEQ ) maybe_relational_exp}
{
  bool maybeRelationalExpOneCorrect = false ;
  Maybe_Relational_Exp( maybeRelationalExpOneCorrect ) ;

  if ( maybeRelationalExpOneCorrect )
    maybeEqualExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "==" || gTempToken.tokenValue == "!=" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeRelationalExpTwoCorrect = false ;
    Maybe_Relational_Exp( maybeRelationalExpTwoCorrect ) ;

    if ( !maybeRelationalExpTwoCorrect )
    {
      maybeEqualExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Maybe_Equality_Exp()

void Rest_Of_Maybe_Bit_AND_Exp( bool& restOfMaybeBitANDExpCorrect )
// rest_of_maybe_bit_AND_exp 
//     : rest_of_maybe_equality_exp { '&' maybe_equality_exp }
{
  bool restOfMaybeEqualExpCorrect = false ;
  Rest_Of_Maybe_Equality_Exp( restOfMaybeEqualExpCorrect ) ;

  if ( restOfMaybeEqualExpCorrect )
    restOfMaybeBitANDExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "&" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeEqualExpCorrect = false ;
    Maybe_Equality_Exp( maybeEqualExpCorrect ) ;

    if ( !maybeEqualExpCorrect )
    {
      restOfMaybeBitANDExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Rest_Of_Maybe_Bit_AND_Exp()

void Maybe_Bit_AND_Exp( bool& maybeBitANDExpCorrect )
// maybe_bit_AND_exp 
//     : maybe_equality_exp { '&' maybe_equality_exp }
{
  bool maybeEqualExpOneCorrect = false ;
  Maybe_Equality_Exp( maybeEqualExpOneCorrect ) ;

  if ( maybeEqualExpOneCorrect )
    maybeBitANDExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "&" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeEqualExpTwoCorrect = false ;
    Maybe_Equality_Exp( maybeEqualExpTwoCorrect ) ;

    if ( !maybeEqualExpTwoCorrect )
    {
      maybeBitANDExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Maybe_Bit_AND_Exp()

void Rest_Of_Maybe_Bit_Ex_OR_Exp( bool& restOfMaybeBitExORExpCorrect )
// rest_of_maybe_bit_ex_OR_exp 
//     : rest_of_maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
{
  bool restOfMaybeBitANDExpCorrect = false ;
  Rest_Of_Maybe_Bit_AND_Exp( restOfMaybeBitANDExpCorrect ) ;

  if ( restOfMaybeBitANDExpCorrect )
    restOfMaybeBitExORExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "^" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeBitANDExpCorrect = false ;
    Maybe_Bit_AND_Exp( maybeBitANDExpCorrect ) ;

    if ( !maybeBitANDExpCorrect )
    {
      restOfMaybeBitExORExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Rest_Of_Maybe_Bit_Ex_OR_Exp()

void Maybe_Bit_Ex_OR_Exp( bool& maybeBitExORExpCorrect )
// maybe_bit_ex_OR_exp 
//     : maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
{
  bool maybeBitANDExpOneCorrect = false ;
  Maybe_Bit_AND_Exp( maybeBitANDExpOneCorrect ) ;

  if ( maybeBitANDExpOneCorrect )
    maybeBitExORExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "^" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeBitANDExpTwoCorrect = false ;
    Maybe_Bit_AND_Exp( maybeBitANDExpTwoCorrect ) ;

    if ( !maybeBitANDExpTwoCorrect )
    {
      maybeBitExORExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while    
} // Maybe_Bit_Ex_OR_Exp()

void Rest_Of_Maybe_Bit_OR_Exp( bool& restOfMaybeBitORExpCorrect )
// rest_of_maybe_bit_OR_exp 
//     : rest_of_maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
{
  bool restOfMaybeBitExORExpCorrect = false ;
  Rest_Of_Maybe_Bit_Ex_OR_Exp( restOfMaybeBitExORExpCorrect ) ;

  if ( restOfMaybeBitExORExpCorrect )
    restOfMaybeBitORExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "|" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeBitExORExpCorrect = false ;
    Maybe_Bit_Ex_OR_Exp( maybeBitExORExpCorrect ) ;

    if ( !maybeBitExORExpCorrect )
    {
      restOfMaybeBitORExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Rest_Of_Maybe_Bit_OR_Exp()

void Maybe_Bit_OR_Exp( bool& maybeBitORExpCorrect )
// maybe_bit_OR_exp 
//     : maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
{
  bool maybeBitExORExpOneCorrect = false ;
  Maybe_Bit_Ex_OR_Exp( maybeBitExORExpOneCorrect ) ;

  if ( maybeBitExORExpOneCorrect )
    maybeBitORExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "|" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeBitExORExpTwoCorrect = false ;
    Maybe_Bit_Ex_OR_Exp( maybeBitExORExpTwoCorrect ) ;

    if ( !maybeBitExORExpTwoCorrect )
    {
      maybeBitORExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while
} // Maybe_Bit_OR_Exp()

void Rest_Of_Maybe_Logical_AND_Exp( bool& restOfMaybeLogicalANDExpCorrect )
// rest_of_maybe_logical_AND_exp 
//     : rest_of_maybe_bit_OR_exp { AND maybe_bit_OR_exp }
{
  bool restOfMaybeBitORExpCorrect = false ;
  Rest_Of_Maybe_Bit_OR_Exp( restOfMaybeBitORExpCorrect ) ;

  if ( restOfMaybeBitORExpCorrect )
    restOfMaybeLogicalANDExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "&&" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeBitORExpCorrect = false ;
    Maybe_Bit_OR_Exp( maybeBitORExpCorrect ) ;

    if ( !maybeBitORExpCorrect )
    {
      restOfMaybeLogicalANDExpCorrect = false ;
      return ;
    } // if 

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while  
} // Rest_Of_Maybe_Logical_AND_Exp()

void Maybe_Logical_AND_Exp( bool& maybeLogicalANDExpCorrect )
// maybe_logical_AND_exp 
//     : maybe_bit_OR_exp { AND maybe_bit_OR_exp }
{
  bool maybeBitORExpOneCorrect = false ;
  Maybe_Bit_OR_Exp( maybeBitORExpOneCorrect ) ;

  if ( maybeBitORExpOneCorrect )
    maybeLogicalANDExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "&&" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeBitORExpTwoCorrect = false ;
    Maybe_Bit_OR_Exp( maybeBitORExpTwoCorrect ) ;

    if ( !maybeBitORExpTwoCorrect )
    {
      maybeLogicalANDExpCorrect = false ;
      return ;
    } // if 

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while
} // Maybe_Logical_AND_Exp()

void Rest_Of_Maybe_Logical_OR_Exp( bool& restOfMaybeLogicalORExpCorrect )
// rest_of_maybe_logical_OR_exp 
//     : rest_of_maybe_logical_AND_exp { OR maybe_logical_AND_exp }
{
  bool restOfMaybeLogicalANDExpCorrect = false ;
  Rest_Of_Maybe_Logical_AND_Exp( restOfMaybeLogicalANDExpCorrect ) ;

  if ( restOfMaybeLogicalANDExpCorrect )
    restOfMaybeLogicalORExpCorrect = true ;
  else
    return ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  while ( gTempToken.tokenValue == "||" )
  {
    GetToken( gCurrentToken ) ;

    bool maybeLogicalANDExpCorrect = false ;
    Maybe_Logical_AND_Exp( maybeLogicalANDExpCorrect ) ;

    if ( !maybeLogicalANDExpCorrect )
    {
      restOfMaybeLogicalORExpCorrect = false ;
      return ;
    } // if

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;   
  } // while
} // Rest_Of_Maybe_Logical_OR_Exp()

void Romce_And_Romloe( bool& romceAndRomloeCorrect )
// rest_of_maybe_conditional_exp_and_rest_of_maybe_logical_OR_exp
//     : rest_of_maybe_logical_OR_exp [ '?' basic_expression ':' basic_expression ]
{
  bool restOfMaybeLogicalORExpCorrect = false ;
  Rest_Of_Maybe_Logical_OR_Exp( restOfMaybeLogicalORExpCorrect ) ;

  if ( restOfMaybeLogicalORExpCorrect )
    romceAndRomloeCorrect = true ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenValue == "?" )
  {
    GetToken( gCurrentToken ) ;

    bool basicOneExprCorrect = false ;
    Basic_Expression( basicOneExprCorrect ) ;

    if ( basicOneExprCorrect )
    {
      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == ":" )
      {
        GetToken( gCurrentToken ) ;

        bool basicTwoExprCorrect = false ;
        Basic_Expression( basicTwoExprCorrect ) ;

        if ( !basicTwoExprCorrect )
          romceAndRomloeCorrect = false ;
      } // if
      else
      {
        romceAndRomloeCorrect = false ;
        gUnexpectedToken = gTempToken.tokenValue ;
      } // else
    } // if
    else
      romceAndRomloeCorrect = false ;
  } // if
} // Romce_And_Romloe()

void Assignment_Operator( bool& asgmtOprCorrect )
// assignment_operator
//     : '=' | TE | DE | RE | PE | ME
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenValue == "="  || gTempToken.tokenValue == "*=" ||
       gTempToken.tokenValue == "/=" || gTempToken.tokenValue == "%=" ||
       gTempToken.tokenValue == "+=" || gTempToken.tokenValue == "-=" )
  {
    GetToken( gCurrentToken ) ;
    asgmtOprCorrect = true ;
  } // if
} // Assignment_Operator()

void Actual_Parameter_List( bool& actualPrmListCorrect )
// actual_parameter_list 
//     : basic_expression { ',' basic_expression }
{
  bool basicOneExprCorrect = false ;
  Basic_Expression( basicOneExprCorrect ) ;

  if ( basicOneExprCorrect )
  {
    actualPrmListCorrect = true ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    while ( gTempToken.tokenValue == "," )
    {
      GetToken( gCurrentToken ) ;

      bool basicTwoExprCorrect = false ;
      Basic_Expression( basicTwoExprCorrect ) ;

      if ( !basicTwoExprCorrect )
      {
        actualPrmListCorrect = false ;
        return ;
      } // if

      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;
    } // while
  } // if
} // Actual_Parameter_List()

void Sign( bool& signCorrect )
// sign
//     : '+' | '-' | '!'
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenValue == "+" || 
       gTempToken.tokenValue == "-" ||
       gTempToken.tokenValue == "!" )
  {
    GetToken( gCurrentToken ) ;
    signCorrect = true ;
  } // if
} // Sign()

void Rest_Of_PPMM_ID_Started_Basic_Exp( bool& restOfPPMMIDStartedBasicExpCorrect )
// rest_of_PPMM_Identifier_started_basic_exp
//     : [ '[' expression ']' ] romce_and_romloe 
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenValue == "[" )
  {
    GetToken( gCurrentToken ) ;

    bool exprCorrect = false ;
    Expression( exprCorrect ) ;

    if ( exprCorrect )
    {
      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == "]" )
        GetToken( gCurrentToken ) ;
      else
      {
        gUnexpectedToken = gTempToken.tokenValue ;
        return ;
      } // else
    } // if
    else
      return ;
  } // if

  bool romceAndRomloeCorrect = false ;
  Romce_And_Romloe( romceAndRomloeCorrect ) ;

  if ( romceAndRomloeCorrect )
    restOfPPMMIDStartedBasicExpCorrect = true ;
} // Rest_Of_PPMM_ID_Started_Basic_Exp()

void Rest_Of_ID_Started_Basic_Exp( bool& restOfIDStartedBasicExpCorrect )
// rest_of_Identifier_started_basic_exp
//     : [ '[' expression ']' ]
//       ( assignment_operator basic_expression 
//         | 
//         [ PP | MM ] romce_and_romloe 
//       )
//     | '(' [ actual_parameter_list ] ')' romce_and_romloe
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenValue == "(" )
  {
    GetToken( gCurrentToken ) ;

    bool actualPrmListCorrect = false ;
    Actual_Parameter_List( actualPrmListCorrect ) ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenValue == ")" )
    {
      GetToken( gCurrentToken ) ;

      bool romceAndRomloeCorrect ;
      Romce_And_Romloe( romceAndRomloeCorrect ) ;

      if ( romceAndRomloeCorrect )
        restOfIDStartedBasicExpCorrect = true ;
    } // if
    else
      gUnexpectedToken = gTempToken.tokenValue ;
  } // if
  else
  {
    if ( gTempToken.tokenValue == "[" )
    {
      GetToken( gCurrentToken ) ;

      bool exprCorrect = false ;
      Expression( exprCorrect ) ;

      if ( exprCorrect )
      {
        if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
          return ;

        if ( gTempToken.tokenValue == "]" )
          GetToken( gCurrentToken ) ;
        else
        {
          gUnexpectedToken = gTempToken.tokenValue ;
          return ;
        } // else
      } // if
      else
        return ;
    } // if

    bool asgmtOprCorrect = false ;
    Assignment_Operator( asgmtOprCorrect ) ;

    if ( asgmtOprCorrect )
    {
      bool basicExprCorrect = false ;
      Basic_Expression( basicExprCorrect ) ;

      if ( basicExprCorrect )
        restOfIDStartedBasicExpCorrect = true ;
    } // if
    else
    {
      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == "++" || gTempToken.tokenValue == "--" )
        GetToken( gCurrentToken ) ;

      bool romceAndRomloeCorrect ;
      Romce_And_Romloe( romceAndRomloeCorrect ) ;

      if ( romceAndRomloeCorrect )
        restOfIDStartedBasicExpCorrect = true ;
    } // else
  } // else
} // Rest_Of_ID_Started_Basic_Exp()

void Basic_Expression( bool& basicExprCorrect )
// basic_expression
//     : Identifier rest_of_Identifier_started_basic_exp
//     | ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
//     | sign { sign } signed_unary_exp romce_and_romloe
//     | ( Constant | '(' expression ')' ) romce_and_romloe
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenType == IDENT )
  {
    if ( gTempToken.tokenValue != "ListAllVariables" && 
         gTempToken.tokenValue != "ListAllFunctions" && 
         gTempToken.tokenValue != "ListVariable"     &&
         gTempToken.tokenValue != "ListFunction"     &&
         gTempToken.tokenValue != "Done"             &&
         gTempToken.tokenValue != "cout"             &&
         gTempToken.tokenValue != "cin" )
    {
      if ( !FindDefinedValue( gTempToken.tokenValue ) )
      {
        gNoDefinedValue = true ;
        return ;
      } // if
    } // if

    GetToken( gCurrentToken ) ;

    bool restOfIDStartedBasicExpCorrect = false ;
    Rest_Of_ID_Started_Basic_Exp( restOfIDStartedBasicExpCorrect ) ;

    if ( restOfIDStartedBasicExpCorrect )
      basicExprCorrect = true ;
  } // if
  else if ( gTempToken.tokenValue == "++" || gTempToken.tokenValue == "--" )
  {
    GetToken( gCurrentToken ) ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenType == IDENT )
    {
      if ( !FindDefinedValue( gTempToken.tokenValue ) )
      {
        gNoDefinedValue = true ;
        return ;
      } // if

      GetToken( gCurrentToken ) ;

      bool restOfPPMMIDStartedBasicExpCorrect = false ;
      Rest_Of_PPMM_ID_Started_Basic_Exp( restOfPPMMIDStartedBasicExpCorrect ) ;

      if ( restOfPPMMIDStartedBasicExpCorrect )
        basicExprCorrect = true ;
    } // if
    else
      gUnexpectedToken = gTempToken.tokenValue ;
  } // else if
  else if ( gTempToken.tokenType == INT   || gTempToken.tokenType == FLOAT  ||
            gTempToken.tokenType == CHAR  || gTempToken.tokenType == STRING ||
            gTempToken.tokenType == BOOL  || gTempToken.tokenValue == "(" )
  {
    if ( gTempToken.tokenValue == "(" )
    {
      GetToken( gCurrentToken ) ;

      bool exprCorrect = false ;
      Expression( exprCorrect ) ;

      if ( exprCorrect )
      {
        if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
          return ;

        if ( gTempToken.tokenValue == ")" )
          GetToken( gCurrentToken ) ;
        else
        {
          gUnexpectedToken = gTempToken.tokenValue ;
          return ;
        } // else
      } // if
      else
        return ;
    } // if
    else // Constant
      GetToken( gCurrentToken ) ;

    bool romceAndRomloeCorrect = false ;
    Romce_And_Romloe( romceAndRomloeCorrect ) ;

    if ( romceAndRomloeCorrect )
      basicExprCorrect = true ;
  } // else if
  else
  {
    bool signOneCorrect = false ;
    Sign( signOneCorrect ) ;

    if ( signOneCorrect )
    {
      bool signTwoCorrect = true ;

      while ( signTwoCorrect )
      {
        signTwoCorrect = false ;
        Sign( signTwoCorrect ) ;
      } // while

      bool signedUnaryExpCorrect = false ;
      Signed_Unary_Exp( signedUnaryExpCorrect ) ;

      if ( signedUnaryExpCorrect )
      {
        bool romceAndRomloeCorrect = false ;
        Romce_And_Romloe( romceAndRomloeCorrect ) ;

        if ( romceAndRomloeCorrect )
          basicExprCorrect = true ;
      } // if
    } // if
  } // else
} // Basic_Expression()

void Expression( bool& exprCorrect )
// expression
//     : basic_expression { ',' basic_expression }
{
  bool basicExprOneCorrect = false ;
  Basic_Expression( basicExprOneCorrect ) ;

  if ( basicExprOneCorrect )
  {
    exprCorrect = true ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    while ( gTempToken.tokenValue == "," )
    {
      GetToken( gCurrentToken ) ;

      bool basicExprTwoCorrect = false ;
      Basic_Expression( basicExprTwoCorrect ) ;

      if ( !basicExprTwoCorrect )
      {
        exprCorrect = false ;
        return ;
      } // if

      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;
    } // while
  } // if
} // Expression()

void Statement( bool& stmtCorrect )
// statement
//     : ';'     // the null statement
//     | expression ';'  /* expression here should not be empty */
//     | RETURN [ expression ] ';'
//     | compound_statement
//     | IF '(' expression ')' statement [ ELSE statement ]
//     | WHILE '(' expression ')' statement
//     | DO statement WHILE '(' expression ')' ';'
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenValue == ";" )
  {
    GetToken( gCurrentToken ) ;
    stmtCorrect = true ;
  } // if
  else if ( gTempToken.tokenValue == "return" )
  {
    GetToken( gCurrentToken ) ;

    bool exprCorrect = false ;
    Expression( exprCorrect ) ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenValue == ";" )
    {
      GetToken( gCurrentToken ) ;
      stmtCorrect = true ;
    } // if
    else
    {
      gUnexpectedToken = gTempToken.tokenValue ;
      gTheEndOfInput = false ;
    } // else
  } // else if
  else if ( gTempToken.tokenValue == "if" )
  {
    GetToken( gCurrentToken ) ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenValue == "(" )
    {
      GetToken( gCurrentToken ) ;

      bool exprCorrect = false ;
      Expression( exprCorrect ) ;

      if ( exprCorrect )
      {
        if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
          return ;

        if ( gTempToken.tokenValue == ")" )
        {
          GetToken( gCurrentToken ) ;

          bool stmtTwoCorrect = false ;
          Statement( stmtTwoCorrect ) ;

          if ( stmtTwoCorrect )
            stmtCorrect = true ;

          if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
            return ;

          if ( gTempToken.tokenValue == "else" )
          {
            GetToken( gCurrentToken ) ;

            bool stmtThreeCorrect = false ;
            Statement( stmtThreeCorrect ) ;

            if ( !stmtThreeCorrect )
              stmtCorrect = false ;
          } // if
        } // if
        else
          gUnexpectedToken = gTempToken.tokenValue ;
      } // if
    } // if
    else
      gUnexpectedToken = gTempToken.tokenValue ;   
  } // else if
  else if ( gTempToken.tokenValue == "while" )
  {
    GetToken( gCurrentToken ) ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenValue == "(" )
    {
      GetToken( gCurrentToken ) ;

      bool exprCorrect = false ;
      Expression( exprCorrect ) ;

      if ( exprCorrect )
      {
        if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
          return ;

        if ( gTempToken.tokenValue == ")" )
        {
          GetToken( gCurrentToken ) ;

          bool stmtTwoCorrect = false ;
          Statement( stmtTwoCorrect ) ;

          if ( stmtTwoCorrect )
            stmtCorrect = true ;
        } // if
        else
          gUnexpectedToken = gTempToken.tokenValue ;
      } // if
    } // if 
    else
      gUnexpectedToken = gTempToken.tokenValue ;
  } // else if
  else if ( gTempToken.tokenValue == "do" )
  {
    GetToken( gCurrentToken ) ;

    bool stmtTwoCorrect = false ;
    Statement( stmtTwoCorrect ) ;

    if ( stmtTwoCorrect )
    {
      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;
      
      if ( gTempToken.tokenValue == "while" )
      {
        GetToken( gCurrentToken ) ;

        if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
          return ;

        if ( gTempToken.tokenValue == "(" )
        {
          GetToken( gCurrentToken ) ;

          bool exprCorrect = false ;
          Expression( exprCorrect ) ;

          if ( exprCorrect )
          {
            if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
              return ;

            if ( gTempToken.tokenValue == ")" )
            {
              GetToken( gCurrentToken ) ;

              if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
                return ;

              if ( gTempToken.tokenValue == ";" )
              {
                GetToken( gCurrentToken ) ;
                stmtCorrect = true ;
              } // if
              else
              {
                gUnexpectedToken = gTempToken.tokenValue ;
                gTheEndOfInput = false ;
              } // else
            } // if
            else
              gUnexpectedToken = gTempToken.tokenValue ;
          } // if 
        } // if
        else
          gUnexpectedToken = gTempToken.tokenValue ;
      } // if
      else
        gUnexpectedToken = gTempToken.tokenValue ;
    } // if
  } // else if
  else
  {
    bool exprCorrect = false ;
    Expression( exprCorrect ) ;

    if ( exprCorrect )
    {
      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == ";" )
      {
        GetToken( gCurrentToken ) ;
        stmtCorrect = true ;
      } // if
      else
      {
        gUnexpectedToken = gTempToken.tokenValue ;
        gTheEndOfInput = false ;
      } // else
    } // if
    else if ( !gNoDefinedValue )
    {
      bool compoundStmtCorrect = false ;
      Compound_Statement( compoundStmtCorrect ) ;

      if ( compoundStmtCorrect )
        stmtCorrect = true ;
    } // else if
  } // else
} // Statement()

void Declaration( bool& dclCorrect )
// declaration 
//     : type_specifier Identifier rest_of_declarators
{
  bool typeSpeciCorrect = false ;
  Type_Specifier( typeSpeciCorrect ) ;

  if ( typeSpeciCorrect )
  {
    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenType == IDENT )
    { 
      GetToken( gCurrentToken ) ;

      bool restOfDclCorrect = false ;
      Rest_Of_Declarators( restOfDclCorrect ) ;

      if ( restOfDclCorrect )
        dclCorrect = true ;
    } // if
    else
      gUnexpectedToken = gTempToken.tokenValue ;
  } // if
} // Declaration()

void Compound_Statement( bool& compoundStmtCorrect )
// compound_statement 
//     : '{' { declaration | statement } '}'
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenValue == "{" )
  {
    GetToken( gCurrentToken ) ;

    gASetOfInput = true ;

    bool dclCorrect = true ;
    bool stmtCorrect = true ;

    while ( dclCorrect || stmtCorrect ) // { declaration | statement }
    {
      dclCorrect = false ;
      Declaration( dclCorrect ) ;
      if ( !dclCorrect )
      {
        stmtCorrect = false ;
        Statement( stmtCorrect ) ;
      } // if
    } // while

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenValue == "}" )
    {
      GetToken( gCurrentToken ) ;
      compoundStmtCorrect = true ;
    } // if
    else
    {
      gUnexpectedToken = gTempToken.tokenValue ;
      gTheEndOfInput = false ;
    } // else
  } // if
  else
    gUnexpectedToken = gTempToken.tokenValue ;
} // Compound_Statement()

void Formal_Parameter_List( bool& formalPrmListCorrect )
// formal_parameter_list 
//     : type_specifier [ '&' ] Identifier [ '[' Constant ']' ] 
//       { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }
{
  LabelOfVar tempVar ;

  bool typeSpeciCorrect = false ;
  Type_Specifier( typeSpeciCorrect ) ;

  if ( typeSpeciCorrect )
  {
    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenValue == "&" )
    {
      GetToken( gCurrentToken ) ;

      gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;
    } // if

    if ( gTempToken.tokenType == IDENT )
    {
      GetToken( gCurrentToken ) ;

      gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

      tempVar.indexOfVarName = gFuncParameters.size() - 1 ; // save the index of var
      tempVar.timesOfArray = -1 ;

      formalPrmListCorrect = true ;

      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == "[" )
      {
        GetToken( gCurrentToken ) ;

        gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

        if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
          return ;

        if ( gTempToken.tokenType == INT  || gTempToken.tokenType == FLOAT  ||
             gTempToken.tokenType == CHAR || gTempToken.tokenType == STRING ||
             gTempToken.tokenType == BOOL ) // Constant
        {
          GetToken( gCurrentToken ) ;

          gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

          tempVar.timesOfArray = gFuncParameters.size() - 1 ;

          if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
            return ;

          if ( gTempToken.tokenValue == "]" )
          {
            GetToken( gCurrentToken ) ;

            gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

            if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
              return ;
          } // if
          else
          {
            formalPrmListCorrect = false ;
            gUnexpectedToken = gTempToken.tokenValue ;
            return ;
          } // else
        } // if
        else
        {
          formalPrmListCorrect = false ;
          gNumOfArrayIsError = true ;
          gUnexpectedToken = gTempToken.tokenValue ;
          return ;
        } // else
      } // if

      gIndexOfDefinedVar.push_back( tempVar ) ;

      while ( gTempToken.tokenValue == "," )
      {
        GetToken( gCurrentToken ) ;

        gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

        bool typeSpeciCorrect = false ;
        Type_Specifier( typeSpeciCorrect ) ;

        if ( typeSpeciCorrect )
        {
          if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
            return ;

          if ( gTempToken.tokenValue == "&" )
          {
            GetToken( gCurrentToken ) ;

            gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

            if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
              return ;
          } // if

          if ( gTempToken.tokenType == IDENT )
          {
            GetToken( gCurrentToken ) ;

            gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

            tempVar.indexOfVarName = gFuncParameters.size() - 1 ; // save the index of var
            tempVar.timesOfArray = -1 ;

            if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
              return ;

            if ( gTempToken.tokenValue == "[" )
            {
              GetToken( gCurrentToken ) ;

              gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

              if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
                return ;

              if ( gTempToken.tokenType == INT  || gTempToken.tokenType == FLOAT  ||
                   gTempToken.tokenType == CHAR || gTempToken.tokenType == STRING ||
                   gTempToken.tokenType == BOOL ) // Constant
              {
                GetToken( gCurrentToken ) ;

                gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

                tempVar.timesOfArray = gFuncParameters.size() - 1 ;

                if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
                  return ;

                if ( gTempToken.tokenValue == "]" )
                {
                  GetToken( gCurrentToken ) ;

                  gFuncParameters.push_back( gCurrentToken.tokenValue ) ;
                } // if
                else
                {
                  formalPrmListCorrect = false ;
                  gUnexpectedToken = gTempToken.tokenValue ;
                  return ;
                } // else
              } // if
              else
              {
                formalPrmListCorrect = false ;
                gNumOfArrayIsError = true ;
                gUnexpectedToken = gTempToken.tokenValue ;
                return ;
              } // else
            } // if
          } // if
          else
          {
            formalPrmListCorrect = false ;
            gUnexpectedToken = gTempToken.tokenValue ;
            return ;
          } // else
        } // if
        else
        {
          formalPrmListCorrect = false ;
          return ;
        } // else

        gIndexOfDefinedVar.push_back( tempVar ) ;

        if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
          return ;
      } // while     
    } // if
    else
      gUnexpectedToken = gTempToken.tokenValue ;
  } // if

  if ( gFuncParameters.size() > 0 )
  {
    SetDefinedLocalVarForParameter() ;
    gFuncParameters.clear() ;
  } // if
} // Formal_Parameter_List()

void Function_Definition_Without_ID( bool& funDefWithoutIDCorrect )
// function_definition_without_ID 
//     : '(' [ VOID | formal_parameter_list ] ')' compound_statement
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;
  
  if ( gTempToken.tokenValue == "(" )
  {
    GetToken( gCurrentToken ) ;

    gInputNowIsFunc = true ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenValue == "void" )
    {
      GetToken( gCurrentToken ) ;

      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;      
    } // if
    else
    {
      bool formalPrmListCorrect = false ;
      Formal_Parameter_List( formalPrmListCorrect ) ;
    } // else

    if ( gTempToken.tokenValue == ")" )
    {
      GetToken( gCurrentToken ) ;

      bool compoundStmtCorrect = false ;
      Compound_Statement( compoundStmtCorrect ) ;

      if ( compoundStmtCorrect )
        funDefWithoutIDCorrect = true ;
    } // if
    else
      gUnexpectedToken = gTempToken.tokenValue ;
  } // if
  else
    gUnexpectedToken = gTempToken.tokenValue ;
} // Function_Definition_Without_ID()

void Rest_Of_Declarators( bool& restOfDclCorrect )
// rest_of_declarators 
//     : [ '[' Constant ']' ] 
//       { ',' Identifier [ '[' Constant ']' ] } ';'
{
  LabelOfVar tempVar ;

  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;
  
  tempVar.indexOfVarName = gTokenList.size() - 1 ; // save the index of var
  tempVar.timesOfArray = -1 ;

  if ( gTempToken.tokenValue == "[" )
  {
    GetToken( gCurrentToken ) ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenType == INT  || gTempToken.tokenType == FLOAT  ||
         gTempToken.tokenType == CHAR || gTempToken.tokenType == STRING ||
         gTempToken.tokenType == BOOL ) // Constant
    {
      GetToken( gCurrentToken ) ;

      tempVar.timesOfArray = gTokenList.size() - 1 ;

      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;
      
      if ( gTempToken.tokenValue == "]" )
      {
        GetToken( gCurrentToken ) ;
        restOfDclCorrect = true ;
      } // if
      else
      {
        gUnexpectedToken = gTempToken.tokenValue ;
        return ;
      } // else
    } // if
    else
    {
      gNumOfArrayIsError = true ;
      gUnexpectedToken = gTempToken.tokenValue ;
      return ;
    } // else

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;    
  } // if

  gIndexOfDefinedVar.push_back( tempVar ) ;

  while ( gTempToken.tokenValue == "," )
  {
    GetToken( gCurrentToken ) ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;

    if ( gTempToken.tokenType == IDENT )
    {
      GetToken( gCurrentToken ) ;

      tempVar.indexOfVarName = gTokenList.size() - 1 ;
      tempVar.timesOfArray = -1 ;

      restOfDclCorrect = true ;

      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
        return ;

      if ( gTempToken.tokenValue == "[" )
      {
        GetToken( gCurrentToken ) ;

        if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
          return ;

        if ( gTempToken.tokenType == INT  || gTempToken.tokenType == FLOAT  ||
             gTempToken.tokenType == CHAR || gTempToken.tokenType == STRING ||
             gTempToken.tokenType == BOOL ) // Constant
        {
          GetToken( gCurrentToken ) ;

          tempVar.timesOfArray = gTokenList.size() - 1 ;

          if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
            return ;

          if ( gTempToken.tokenValue == "]" )
            GetToken( gCurrentToken ) ;
          else
          {
            restOfDclCorrect = false ;
            gUnexpectedToken = gTempToken.tokenValue ;
            return ;
          } // else
        } // if
        else
        {
          restOfDclCorrect = false ;
          gNumOfArrayIsError = true ;
          gUnexpectedToken = gTempToken.tokenValue ;
          return ;
        } // else
      } // if
    } // if
    else
    {
      restOfDclCorrect = false ;
      gUnexpectedToken = gTempToken.tokenValue ;
      return ;
    } // else

    gIndexOfDefinedVar.push_back( tempVar ) ;

    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
      return ;
  } // while

  if ( gTempToken.tokenValue != ";" )
  {
    restOfDclCorrect = false ;
    gTheEndOfInput = false ;
    gUnexpectedToken = gTempToken.tokenValue ;
  } // if
  else // ;
  {
    if ( gASetOfInput )
      SetDefinedLocalVar() ;
    else
      gVarDeclar = true ;

    GetToken( gCurrentToken ) ; 
    restOfDclCorrect = true ;
  } // else
} // Rest_Of_Declarators()

void Function_Definition_Or_Declarators( bool& funDefOrDclCorrect )
// function_definition_or_declarators 
//     : function_definition_without_ID
//     | rest_of_declarators
{
  bool funDefWithoutIDCorrect = false ;
  Function_Definition_Without_ID( funDefWithoutIDCorrect ) ;

  if ( funDefWithoutIDCorrect )
    funDefOrDclCorrect = true ;
  else
  {
    bool restOfDclCorrect = false ;
    Rest_Of_Declarators( restOfDclCorrect ) ;

    if ( restOfDclCorrect )
      funDefOrDclCorrect = true ;
  } // else
} // Function_Definition_Or_Declarators()

void Type_Specifier( bool& typeSpeciCorrect )
// type_specifier 
//     : INT | CHAR | FLOAT | STRING | BOOL
{
  if ( gScannerCorrect && !gNoDefinedValue && !Scanner() )
    return ;

  if ( gTempToken.tokenValue == "int"   || gTempToken.tokenValue == "char"   ||
       gTempToken.tokenValue == "float" || gTempToken.tokenValue == "string" ||
       gTempToken.tokenValue == "bool" )
  {
    GetToken( gCurrentToken ) ;

    if ( gInputNowIsFunc )
      gFuncParameters.push_back( gCurrentToken.tokenValue ) ;

    typeSpeciCorrect = true ;
  } // if
  else
    gUnexpectedToken = gTempToken.tokenValue ;
} // Type_Specifier()

void Definition( bool& defCorrect )
// definition 
//     :           VOID Identifier function_definition_without_ID 
//     | type_specifier Identifier function_definition_or_declarators

{
  bool typeSpeciCorrect = false ;
  Type_Specifier( typeSpeciCorrect ) ;

  if ( typeSpeciCorrect )
  {
    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() ) 
      return ;
      
    if ( gTempToken.tokenType == IDENT )
    {
      GetToken( gCurrentToken ) ;

      bool funDefOrDclCorrect = false ;
      Function_Definition_Or_Declarators( funDefOrDclCorrect ) ;

      if ( funDefOrDclCorrect )
      {
        defCorrect = true ;
        gFuncDeclar = true ;
      } // if
    } // if
    else
      gUnexpectedToken = gTempToken.tokenValue ;
  } // if
  else
  {
    if ( gScannerCorrect && !gNoDefinedValue && !Scanner() ) 
      return ; 

    if ( gTempToken.tokenValue == "void" )
    {
      GetToken( gCurrentToken ) ;

      gInputNowIsFunc = true ;

      if ( gScannerCorrect && !gNoDefinedValue && !Scanner() ) 
        return ;

      if ( gTempToken.tokenType == IDENT )
      {
        GetToken( gCurrentToken ) ;

        bool funDefWithoutIDCorrect = false ;
        Function_Definition_Without_ID( funDefWithoutIDCorrect ) ;

        if ( funDefWithoutIDCorrect )
        {
          defCorrect = true ;
          gFuncDeclar = true ;
        } // if
      } // if
      else
        gUnexpectedToken = gTempToken.tokenValue ;
    } // if
    else
      gUnexpectedToken = gTempToken.tokenValue ;
  } // else  
} // Definition()

void User_Input( bool& userInputCorrect )
// user_input 
//     : ( definition | statement ) { definition | statement }
{
  bool stmtCorrect = false ;
  bool defCorrect = false ;

  Definition( defCorrect ) ;

  if ( defCorrect )
    userInputCorrect = true ;
  else if ( gTheEndOfInput && !gNumOfArrayIsError )
  {
    Statement( stmtCorrect ) ;

    if ( stmtCorrect )
      userInputCorrect = true ;    
  } // else if
} // User_Input()

bool FindDefinedValue( string definedVal )
{
  if ( gASetOfInput                                            && 
       gMapVar.find( definedVal ) == gMapVar.end()             &&
       gMapLocalVar.find( definedVal ) == gMapLocalVar.end()   &&
       gMapFunc.find( definedVal ) == gMapFunc.end() )
  {
    PrintErrorMessage( EVALUATOR_ERROR, definedVal ) ;
    return false ;
  } // if 
  else if ( !gASetOfInput                                && 
            gMapVar.find( definedVal ) == gMapVar.end()  &&
            gMapFunc.find( definedVal ) == gMapFunc.end() )
  {
    PrintErrorMessage( EVALUATOR_ERROR, definedVal ) ;
    return false ;
  } // else if
  else
    return true ;
} // FindDefinedValue()

bool Parser()
// when User_Input()'s userInputCorrect is false, 
// it means that it may be scanner error or parser error
{
  gUnexpectedToken = "" ;
  gScannerCorrect = true ;
  gInputNowIsFunc = false ;
  gVarDeclar = false ;
  gFuncDeclar = false ;
  gASetOfInput = false ;
  gNoDefinedValue = false ;
  gNumOfArrayIsError = false ;
  gTheEndOfInput = true ;
  gCleanWhiteSpaceAfterInput = false ;

  gCurrentLine = 1 ;

  bool userInputCorrect = false ;
  User_Input( userInputCorrect ) ;

  if ( userInputCorrect )
    return true ;
  else
  {
    if ( gScannerCorrect && !gNoDefinedValue ) 
      PrintErrorMessage( PARSER_ERROR, gUnexpectedToken ) ;

    return false ;
  } // else

  gUnexpectedToken = "" ;
} // Parser()

void SetDefinedLocalVarForParameter()
{
  string definedLocalVarName = "" ;
  LabelOfToken definedLocalVarValue ;

  if ( gFuncParameters.at( 0 ) == "int" )
    definedLocalVarValue.tokenType = INT ;
  else if ( gFuncParameters.at( 0 ) == "char" )
    definedLocalVarValue.tokenType = CHAR ;
  else if ( gFuncParameters.at( 0 ) == "float" )
    definedLocalVarValue.tokenType = FLOAT ;
  else if ( gFuncParameters.at( 0 ) == "string" )
    definedLocalVarValue.tokenType = STRING ;
  else if ( gFuncParameters.at( 0 ) == "bool" )
    definedLocalVarValue.tokenType = BOOL ;
  definedLocalVarValue.tokenValue = "" ;

  for ( int i = 0 ; i < gIndexOfDefinedVar.size() ; i++ )
  {
    int tempOfIndexName = gIndexOfDefinedVar.at( i ).indexOfVarName ;
    int tempOfIndexTimesOfArray = gIndexOfDefinedVar.at( i ).timesOfArray ;

    definedLocalVarName = gFuncParameters.at( tempOfIndexName ) ;

    if ( gMapLocalVar.find( definedLocalVarName ) == gMapLocalVar.end() )
    { 
      if ( tempOfIndexTimesOfArray != -1 )
        definedLocalVarValue.array_size = gFuncParameters.at( tempOfIndexTimesOfArray ) ;
      gMapLocalVar[definedLocalVarName] = definedLocalVarValue ;
    } // if
    else
    // has defined var
    {
      gMapLocalVar.erase( definedLocalVarName ) ;
      if ( tempOfIndexTimesOfArray != -1 )
        definedLocalVarValue.array_size = gFuncParameters.at( tempOfIndexTimesOfArray ) ;
      gMapLocalVar[definedLocalVarName] = definedLocalVarValue ;
    } // else
  } // for
} // SetDefinedLocalVarForParameter()

void SetDefinedLocalVar()
{
  string definedLocalVarName = "" ;
  LabelOfToken definedLocalVarValue ;

  if ( gTokenList.at( 0 ).tokenValue == "int" )
    definedLocalVarValue.tokenType = INT ;
  else if ( gTokenList.at( 0 ).tokenValue == "char" )
    definedLocalVarValue.tokenType = CHAR ;
  else if ( gTokenList.at( 0 ).tokenValue == "float" )
    definedLocalVarValue.tokenType = FLOAT ;
  else if ( gTokenList.at( 0 ).tokenValue == "string" )
    definedLocalVarValue.tokenType = STRING ;
  else if ( gTokenList.at( 0 ).tokenValue == "bool" )
    definedLocalVarValue.tokenType = BOOL ;
  definedLocalVarValue.tokenValue = "" ;

  for ( int i = 0 ; i < gIndexOfDefinedVar.size() ; i++ )
  {
    int tempOfIndexName = gIndexOfDefinedVar.at( i ).indexOfVarName ;
    int tempOfIndexTimesOfArray = gIndexOfDefinedVar.at( i ).timesOfArray ;

    definedLocalVarName = gTokenList.at( tempOfIndexName ).tokenValue ;

    if ( gMapLocalVar.find( definedLocalVarName ) == gMapLocalVar.end() )
    { 
      if ( tempOfIndexTimesOfArray != -1 )
        definedLocalVarValue.array_size = gTokenList.at( tempOfIndexTimesOfArray ).tokenValue ;
      gMapLocalVar[definedLocalVarName] = definedLocalVarValue ;
    } // if
    else
    // has defined var
    {
      gMapLocalVar.erase( definedLocalVarName ) ;
      if ( tempOfIndexTimesOfArray != -1 )
        definedLocalVarValue.array_size = gTokenList.at( tempOfIndexTimesOfArray ).tokenValue ;
      gMapLocalVar[definedLocalVarName] = definedLocalVarValue ;
    } // else
  } // for
} // SetDefinedLocalVar()

void SetDefinedVar()
{
  string definedVarName = "" ;
  LabelOfToken definedVarValue ;

  if ( gTokenList.at( 0 ).tokenValue == "int" )
    definedVarValue.tokenType = INT ;
  else if ( gTokenList.at( 0 ).tokenValue == "char" )
    definedVarValue.tokenType = CHAR ;
  else if ( gTokenList.at( 0 ).tokenValue == "float" )
    definedVarValue.tokenType = FLOAT ;
  else if ( gTokenList.at( 0 ).tokenValue == "string" )
    definedVarValue.tokenType = STRING ;
  else if ( gTokenList.at( 0 ).tokenValue == "bool" )
    definedVarValue.tokenType = BOOL ;
  definedVarValue.tokenValue = "" ;

  for ( int i = 0 ; i < gIndexOfDefinedVar.size() ; i++ )
  {
    int tempOfIndexName = gIndexOfDefinedVar.at( i ).indexOfVarName ;
    int tempOfIndexTimesOfArray = gIndexOfDefinedVar.at( i ).timesOfArray ;

    definedVarName = gTokenList.at( tempOfIndexName ).tokenValue ;

    if ( gMapVar.find( definedVarName ) == gMapVar.end() )
    { 
      gAllOfVarName.push_back( definedVarName ) ;
      BubbleSort( gAllOfVarName ) ;
      
      if ( tempOfIndexTimesOfArray != -1 )
      {
        definedVarValue.array_size = gTokenList.at( tempOfIndexTimesOfArray ).tokenValue ;

        int numOfArray = atoi( definedVarValue.array_size.c_str() ) ;
        for ( int i = 0 ; i < numOfArray ; i++ )
        {
          string strTemp = "" ;
          stringstream intToString ; // type conversion
          intToString << i ;    // int
          intToString >> strTemp ;  // string 
      
          strTemp = definedVarName + "[" + strTemp + "]" ;
          gMapVar[strTemp].tokenValue = "" ;
        } // for
      } // if
      
      gMapVar[definedVarName] = definedVarValue ;
      cout << "Definition of " << definedVarName << " entered ..." << endl ;
    } // if
    else
    // has defined var
    {
      int oldTimes = atoi( gMapVar[definedVarName].array_size.c_str() ) ;
      gMapVar.erase( definedVarName ) ;

      if ( tempOfIndexTimesOfArray != -1 )
      {
        for ( int i = 0 ; i < oldTimes ; i++ )
        {
          string strTemp = "" ;
          stringstream intToString ; // type conversion
          intToString << i ;    // int
          intToString >> strTemp ;  // string 
      
          strTemp = definedVarName + "[" + strTemp + "]" ;
          gMapVar.erase( strTemp ) ;
        } // for

        definedVarValue.array_size = gTokenList.at( tempOfIndexTimesOfArray ).tokenValue ;
        
        int numOfArray = atoi( definedVarValue.array_size.c_str() ) ;
        for ( int i = 0 ; i < numOfArray ; i++ )
        {
          string strTemp = "" ;
          stringstream intToString ; // type conversion
          intToString << i ;    // int
          intToString >> strTemp ;  // string 
      
          strTemp = definedVarName + "[" + strTemp + "]" ;
          gMapVar[strTemp].tokenValue = "" ;
        } // for        
      } // if

      gMapVar[definedVarName] = definedVarValue ;
      cout << "New definition of " << definedVarName << " entered ..." << endl ;
    } // else
  } // for
} // SetDefinedVar()

void SetDefinedFunc()
{
  string definedFuncName = "" ;
  vector<string> definedFuncValue ;

  definedFuncName = gTokenList.at( 1 ).tokenValue ;

  // reload to a new data in the format of the output function
  int numOfLeftBracket = 0 ;
  for ( int i = 0 ; i < gTokenList.size() ; i++ )
  {
    if ( i == 1 || gMapFunc.find( gTokenList.at( i ).tokenValue ) != gMapFunc.end() )
      definedFuncValue.push_back( gTokenList.at( i ).tokenValue ) ;      
    else if ( gTokenList.at( i ).tokenValue == "{" )
    {
      definedFuncValue.push_back( gTokenList.at( i ).tokenValue ) ;
      definedFuncValue.push_back( "\n" ) ;

      numOfLeftBracket++ ;

      for ( int i = numOfLeftBracket ; i > 0 ; i-- )
        definedFuncValue.push_back( "  " ) ;
    } // else if
    else if ( gTokenList.at( i ).tokenValue == "}" )
    {
      definedFuncValue.pop_back() ;
      numOfLeftBracket-- ;

      definedFuncValue.push_back( gTokenList.at( i ).tokenValue ) ; // }
      definedFuncValue.push_back( "\n" ) ;

      for ( int i = numOfLeftBracket ; i > 0 ; i-- )
        definedFuncValue.push_back( "  " ) ;
    } // else if
    else if ( gTokenList.at( i ).tokenValue == "["    ||
              gTokenList.at( i ).tokenValue == "++"   ||
              gTokenList.at( i ).tokenValue == "--"   ||
              gTokenList.at( i ).tokenValue == ","    ||
              ( gTokenList.at( i ).tokenValue == ")"  && 
                gTokenList.at( i-1 ).tokenValue == "(" ) )
    {
      definedFuncValue.pop_back() ;
      definedFuncValue.push_back( gTokenList.at( i ).tokenValue ) ;
      definedFuncValue.push_back( " " ) ;
    } // else if
    else if ( gTokenList.at( i ).tokenValue == ";" )
    {
      definedFuncValue.push_back( gTokenList.at( i ).tokenValue ) ;
      definedFuncValue.push_back( "\n" ) ;

      for ( int i = numOfLeftBracket ; i > 0 ; i-- )
        definedFuncValue.push_back( "  " ) ;
    } // else if
    else
    {
      definedFuncValue.push_back( gTokenList.at( i ).tokenValue ) ;
      definedFuncValue.push_back( " " ) ;
    } // else
  } // for

  if ( gMapFunc.find( definedFuncName ) == gMapFunc.end() )
  { 
    gAllOfFuncName.push_back( definedFuncName ) ;
    BubbleSort( gAllOfFuncName ) ;
    gMapFunc[definedFuncName] = definedFuncValue ;
    cout << "Definition of " << definedFuncName << "()" << " entered ..." << endl ;
  } // if
  else
  // has defined var
  {
    gMapVar.erase( definedFuncName ) ;
    gMapFunc[definedFuncName] = definedFuncValue ;
    cout << "New definition of " << definedFuncName << "()" << " entered ..." << endl ;
  } // else
} // SetDefinedFunc()

void DealWithEXEC()
{
  if ( gVarDeclar )
    SetDefinedVar() ;
  else if ( gFuncDeclar )  
    SetDefinedFunc() ;
  else
  {
    EXECmd() ;
    cout << "Statement executed ..." << endl ;
  } // else

  if ( gASetOfInput )
    gMapLocalVar.clear() ;
} // DealWithEXEC()

bool GrabParm( string& parameter )
// when there are parentheses
// take the value inside the parentheses
{
  parameter = "" ;
  int i = 0 ;
  int numOfParameter = 0 ;

  while ( gTokenList.at( i ).tokenValue != "(" )
    i++ ;
  i ++ ;

  while ( gTokenList.at( i ).tokenValue != ")" )
  {
    parameter = gTokenList.at( i ).tokenValue ;
    numOfParameter++ ;
    i ++ ;
  } // while

  if ( numOfParameter == 1 )
    return true ;
  else
    return false ; 
} // GrabParm()

void BubbleSort( vector<string>& vectorOfDef )
// sort from smallest to largest
{
  for ( int i = 0 ; i < vectorOfDef.size()-1 ; i++ ) 
  {
    for ( int j = 0 ; j < vectorOfDef.size()-i-1 ; j++ ) 
    {
      if ( vectorOfDef.at( j ) > vectorOfDef.at( j+1 ) ) 
      {
        string tempOfStr = vectorOfDef.at( j ) ;
        vectorOfDef.at( j ) = vectorOfDef.at( j+1 ) ;
        vectorOfDef.at( j+1 ) = tempOfStr ;
      } // if
    } // for
  } // for
} // BubbleSort()

EvalType ClassForEvalType( string& parameter )
// divide commands into different types of processing
{
  parameter = "" ;

  LabelOfToken command ;
  command.tokenValue = "" ;

  command.tokenValue = gTokenList.at( 0 ).tokenValue ;
  command.tokenType = gTokenList.at( 0 ).tokenType ;

  if ( command.tokenValue == "ListAllVariables" )
  {
    if ( !GrabParm( parameter ) )
      return LIST_ALL_VAR ;
    else
      return EXEC ; 
  } // if
  else if ( command.tokenValue == "ListAllFunctions" )
  {
    if ( !GrabParm( parameter ) )
      return LIST_ALL_FUNC ;
    else
      return EXEC ;
  } // else if
  else if ( command.tokenValue == "ListVariable" )
  {
    if ( GrabParm( parameter ) )
      return LIST_VAR ;
    else
      return EXEC ;
  } // else if
  else if ( command.tokenValue == "ListFunction" )
  {
    if ( GrabParm( parameter ) )
      return LIST_FUNC ;
    else
      return EXEC ;
  } // else if
  else if ( command.tokenValue == "Done" )
  {
    if ( !GrabParm( parameter ) )
      return DONE ;
    else
      return EXEC ;
  } // else if
  else
    return EXEC ;
} // ClassForEvalType()

void Evaluator()
// Process the output of different instructions separately
{
  string parameter = "" ;
  EvalType evalType ;

  evalType = ClassForEvalType( parameter ) ;

  if ( evalType == LIST_ALL_VAR )
  // ListAllVariables()
  {
    for ( int i = 0 ; i < gAllOfVarName.size() ; i++ )
      cout << gAllOfVarName.at( i ) << endl ;

    cout << "Statement executed ..." << endl ;
  } // if
  else if ( evalType == LIST_ALL_FUNC )
  // LsitAllFunctions()
  {
    for ( int i = 0 ; i < gAllOfFuncName.size() ; i++ )
      cout << gAllOfFuncName.at( i ) << "()" << endl ;

    cout << "Statement executed ..." << endl ;
  } // else if
  else if ( evalType == LIST_VAR )
  // ListVariable( var name )
  {
    parameter.erase( 0, 1 ) ; // remove the left "
    parameter.erase( parameter.size()-1, 1 ) ; // remove the right "

    if ( gMapVar.find( parameter ) != gMapVar.end() ) 
    {
      LabelOfToken definedVar = gMapVar[parameter] ;

      if ( definedVar.tokenType == INT )
        cout << "int " ;
      else if ( definedVar.tokenType == FLOAT )
        cout << "float " ;
      else if ( definedVar.tokenType == CHAR )
        cout << "char " ;
      else if ( definedVar.tokenType == STRING )
        cout << "string " ;
      else if ( definedVar.tokenType == BOOL )
        cout << "bool " ;

      if ( !definedVar.array_size.empty() )
        cout << parameter << "[ " << definedVar.array_size << " ] ;" << endl ;
      else
        cout << parameter << " ;" << endl ;
    } // if

    cout << "Statement executed ..." << endl ;
  } // else if
  else if ( evalType == LIST_FUNC )
  // listFunction( function's name )
  {
    parameter.erase( 0, 1 ) ; // remove the left "
    parameter.erase( parameter.size()-1, 1 ) ; // remove the right "

    if ( gMapFunc.find( parameter ) != gMapFunc.end() ) 
    {
      vector<string> definedFunc = gMapFunc[parameter] ;

      for ( int i = 0 ; i < definedFunc.size() ; i++ )
        cout << definedFunc.at( i ) ;
    
    } // if

    cout << "Statement executed ..." << endl ;
  } // else if
  else if ( evalType == EXEC )
  // variable declaration, function declaration
  // and other instructions ( ex. if(-else), while )
    DealWithEXEC() ;
  else 
  // Done()
  // end program execution
    gQuit = true ;

  
  if ( gTempToken.tokenValue.empty() && !gQuit )
  {
    gCleanWhiteSpaceAfterInput = true ;
    bool notInitial = PeekToken( gTempToken ) ;
    
    if ( !notInitial )
      gTempToken.tokenValue = "" ;
  } // if
} // Evaluator()

void EXECmd()
{
  vector<LabelOfToken> tempTokenList ;
  vector<string> postfixTokenList ;
  ReorganizeTokenList( tempTokenList ) ;

  if ( gTokenList.at( 0 ).tokenValue == "cout" )
  {    
    vector<LabelOfToken> splitTokenList ;

    for ( int i = 1 ; i < tempTokenList.size() ; i++ )
    {
      string strTemp = "" ;

      if ( tempTokenList.at( i ).tokenValue != "<<" &&
           tempTokenList.at( i ).tokenValue != ";" )
        splitTokenList.push_back( tempTokenList.at( i ) ) ;
      else if ( tempTokenList.at( i ).tokenValue == "<<" &&
                tempTokenList.at( i+1 ).tokenType == INT &&
                tempTokenList.at( i-1 ).tokenValue != "cout" )
        splitTokenList.push_back( tempTokenList.at( i ) ) ;
      else if ( tempTokenList.at( i ).tokenValue == "<<" ||
                tempTokenList.at( i ).tokenValue == ";" )
      {
        if ( !splitTokenList.empty() )
        {
          // AddConEndOP( splitTokenList ) ;
          InToPoAndRepDef( postfixTokenList, splitTokenList ) ;
          strTemp = CalPostfixVal( postfixTokenList ) ;

          if ( IsString( strTemp ) )
            strTemp = strTemp.substr( 1, strTemp.length()-2 ) ;
        
          for ( int i = 0 ; i < strTemp.length() ; i++ )
          {
            char charTemp = strTemp.c_str()[i] ;

            if ( ( charTemp == '\\' && strTemp.c_str()[i+1] == 'n' ) ||
                 charTemp == '\n' )
            {
              if ( charTemp == '\\' && strTemp.c_str()[i+1] == 'n' )
                i++ ;
              charTemp = '\0' ;
              cout << "\n" ;
            } // if
            else
              cout << charTemp ;
          } // for

          splitTokenList.clear() ;
          postfixTokenList.clear() ;
        } // if
      } // else if
    } // for
  } // if
  else if ( ( gTokenList.at( 0 ).tokenType == IDENT &&
              gTokenList.at( 1 ).tokenValue == "=" ) ||
            ( gTokenList.at( 0 ).tokenType == IDENT &&
              gMapVar.find( gTokenList.at( 0 ).tokenValue ) != gMapVar.end() ) )
  {
    tempTokenList.pop_back() ; // remove ;
    InToPoAndRepDef( postfixTokenList, tempTokenList ) ;
    CalPostfixVal( postfixTokenList ) ;
    postfixTokenList.clear() ;
  } // else if

  tempTokenList.clear() ;
} // EXECmd()

void InToPoAndRepDef(  vector<string>& postfixTokenList, 
                       vector<LabelOfToken>& infixTokenList )
// infix lexemes to postfix lexemes
// replace the defined IDENT with the defined value
{ 
  string strDefinedValue = "" ;
  string stackOfOperator[MAX] ;
  map<string, bool > boolOfNewID ;
  vector<string> newDefinedID ;
  int indexOfNewIDName = 0 ;

  int i, top ;
  for ( i = 0, top = 0 ; i < infixTokenList.size() ; i++ )  
  {
    if ( ( i == 0 && 
           ( infixTokenList.at( i ).tokenValue == "+" ||
             infixTokenList.at( i ).tokenValue == "-" || 
             infixTokenList.at( i ).tokenValue == "!" ) ) ||
         ( i != 0 && 
           ( infixTokenList.at( i ).tokenValue == "+" ||
             infixTokenList.at( i ).tokenValue == "-" ||
             infixTokenList.at( i ).tokenValue == "!" ) &&          
           ( infixTokenList.at( i-1 ).tokenType == OP ||
             infixTokenList.at( i-1 ).tokenValue == "(" ) ) )
    {
      if ( infixTokenList.at( i ).tokenValue == "+" )
        strDefinedValue = "@+" ;
      else if ( infixTokenList.at( i ).tokenValue == "-" )
        strDefinedValue = "@-" ;
      else
        strDefinedValue = "!" ;
      
      stackOfOperator[++top] = strDefinedValue ; // save to stack      
    } // if
    else if ( infixTokenList.at( i ).tokenValue == "(" ) // save to stack
      stackOfOperator[++top] = infixTokenList.at( i ).tokenValue;
    else if ( infixTokenList.at( i ).tokenValue == ")" )
    {
      while ( stackOfOperator[top] != "(" )
      // meet ) and then output the stack to postfix untill meet ( 
      {
        if ( PriForCal( stackOfOperator[top] ) == 1 )
        {
          indexOfNewIDName = newDefinedID.size() - 1 ;
          boolOfNewID[ newDefinedID.at( indexOfNewIDName ) ] = true ;
          newDefinedID.pop_back() ;
        } // if

        postfixTokenList.push_back( stackOfOperator[top--] ) ;
      } // while

      top-- ;  // should not output (
    } // else if 
    else if ( infixTokenList.at( i ).tokenValue == "++" || 
              infixTokenList.at( i ).tokenValue == "--" )
    {
      if ( ( i+1 <= infixTokenList.size()-1 ) && 
           ( infixTokenList.at( i+1 ).tokenType == IDENT ) ) // ++a
      {
        strDefinedValue = gMapVar[infixTokenList.at( i+1 ).tokenValue].tokenValue ;
        int iTemp = atoi( strDefinedValue.c_str() ) ;
        string strTemp = infixTokenList.at( i ).tokenValue ;

        if ( strTemp == "++" )
          iTemp++ ;
        else
          iTemp-- ;
        
        stringstream intToString ; // type conversion
        intToString << iTemp ;    // int
        intToString >> strTemp ;  // string
        gMapVar[infixTokenList.at( i+1 ).tokenValue].tokenValue = strTemp ;
      } // if
      else if ( i != 0 &&
                infixTokenList.at( i-1 ).tokenType == IDENT ) // a++
      {
        strDefinedValue = gMapVar[infixTokenList.at( i-1 ).tokenValue].tokenValue ;
        int iTemp = atoi( strDefinedValue.c_str() ) ;
        string strTemp = infixTokenList.at( i ).tokenValue ;

        if ( strTemp == "++" )
          iTemp++ ;
        else
          iTemp-- ;
        
        stringstream intToString ; // type conversion
        intToString << iTemp ;     // int
        intToString >> strTemp ;   // string
        gMapVar[infixTokenList.at( i-1 ).tokenValue].tokenValue = strTemp ;
      } // else if

      infixTokenList.at( i ).tokenType = NON ;
    } // else if
    else if ( infixTokenList.at( i ).tokenValue == "?" )
    {
      stackOfOperator[++top] = infixTokenList.at( i ).tokenValue ;
    } // else if 
    else if ( infixTokenList.at( i ).tokenValue == ":" )
    {
      while ( stackOfOperator[top] != "?" )
        postfixTokenList.push_back( stackOfOperator[top--] ) ;

      postfixTokenList.push_back( stackOfOperator[top--] ) ;
      stackOfOperator[++top] = infixTokenList.at( i ).tokenValue ;
    } // else if
    else if ( infixTokenList.at( i ).tokenType == OP )
    {
      int priPre = PriForCal( stackOfOperator[top] ) ;
      int priNow = PriForCal( infixTokenList.at( i ).tokenValue ) ;

      while ( priPre >= priNow )
      { 
        if ( priPre != 1 && priNow != 1 )
        {
          postfixTokenList.push_back( stackOfOperator[top--] ) ;

          if ( priPre == 1 )
          {
            indexOfNewIDName = newDefinedID.size() - 1 ;
            boolOfNewID[ newDefinedID.at( indexOfNewIDName ) ] = true ;
            newDefinedID.pop_back() ;
          } // if

          priPre = PriForCal( stackOfOperator[top] ) ;
          priNow = PriForCal( infixTokenList.at( i ).tokenValue ) ;
        } // if
        else
          priPre = -1 ;
      } // while
      
      stackOfOperator[++top] = infixTokenList.at( i ).tokenValue ; // save to stack
    } // else if
    else if ( infixTokenList.at( i ).tokenValue == "," )
    {
      if ( newDefinedID.size() > 0 )
      {
        indexOfNewIDName = newDefinedID.size() - 1 ;
        boolOfNewID[ newDefinedID.at( indexOfNewIDName ) ] = true ;
        newDefinedID.pop_back() ;
      } // if

      while ( stackOfOperator[top] != "(" )
        postfixTokenList.push_back( stackOfOperator[top--] ) ;

      postfixTokenList.push_back( infixTokenList.at( i ).tokenValue ) ;
    } // else if
    else // output the operator to postfix 
    {
      if ( infixTokenList.at( i ).tokenType == IDENT )
      {
        if ( i+1 <= infixTokenList.size()-1 )
        {
          if ( infixTokenList.at( i+1 ).tokenValue != "="  &&
               infixTokenList.at( i+1 ).tokenValue != "+=" && 
               infixTokenList.at( i+1 ).tokenValue != "-=" &&
               infixTokenList.at( i+1 ).tokenValue != "*=" &&
               infixTokenList.at( i+1 ).tokenValue != "/=" &&
               infixTokenList.at( i+1 ).tokenValue != "%=" )
          {
            if ( boolOfNewID[infixTokenList.at( i ).tokenValue] == true )
              strDefinedValue = "#" + infixTokenList.at( i ).tokenValue ;
            else
              strDefinedValue = gMapVar[infixTokenList.at( i ).tokenValue].tokenValue ;
            
            postfixTokenList.push_back( strDefinedValue ) ;
          } // if
          else
          {
            boolOfNewID[infixTokenList.at( i ).tokenValue] = false ;
            newDefinedID.push_back( infixTokenList.at( i ).tokenValue ) ;
            postfixTokenList.push_back( infixTokenList.at( i ).tokenValue ) ;
          } // else
        } // if
        else 
        {
          if ( boolOfNewID[infixTokenList.at( i ).tokenValue] == true )
            strDefinedValue = "#" + infixTokenList.at( i ).tokenValue ;
          else
            strDefinedValue = gMapVar[infixTokenList.at( i ).tokenValue].tokenValue ;
          
          postfixTokenList.push_back( strDefinedValue ) ;
        } // else
      } // if
      else
        postfixTokenList.push_back( infixTokenList.at( i ).tokenValue ) ;
    } // else
  } // for

  while ( top > 0 ) // stack[0]=NULL // output remaining characters to postfix
    postfixTokenList.push_back( stackOfOperator[top--] ) ;
  
  boolOfNewID.clear() ;
  newDefinedID.clear() ;
} // InToPoAndRepDef()

int PriForCal( string op )
// +, - has less priority than *, /, %
// &&, ||, <, <=, >, >=
// <<, >>
// ==, !=
{
  if ( op == "+" || op == "-" ) 
    return 5 ;
  else if ( op == "*"  || op == "/"  || op == "%" || 
            op == ">>" || op == "<<" )
    return 6 ;
  else if ( op == "<"  || op == "<=" || op == ">"  || 
            op == ">=" || op == "==" || op == "!=" )
    return 4 ;
  else if ( op == "&&" || op == "||" )
    return 3 ;
  else if ( op == "?" || op == ":" )
    return 2 ;
  else if ( op == "@+" || op == "@-" || op == "!" )
    return 6 ;
  else if ( op == "="  || op == "+=" || op == "-=" ||
            op == "*=" || op == "/=" || op == "%=" )
    return 1 ;
  else
    return 0 ;
} // PriForCal()

string CalPostfixVal( vector<string>& postfixTokenList ) 
// stackValue is where numbers are stored
// take out the top two digits of the stackValue for calculation 
// and put them back to the top
// the last remaining top value is the last calculated result
{
  string stackValue[MAX] = {""} ;
  string strCalValue = "" ;

  int i, top ;
  for ( i = 0, top = 0 ; i < postfixTokenList.size() ; i++ ) 
  { 
    if ( postfixTokenList.at( i ) == "+"  || postfixTokenList.at( i ) == "-"  || 
         postfixTokenList.at( i ) == "*"  || postfixTokenList.at( i ) == "/"  ||
         postfixTokenList.at( i ) == "%"  || postfixTokenList.at( i ) == ">>" || 
         postfixTokenList.at( i ) == "<<" ) 
    { // grab 2 numers of stack and calculate
      strCalValue = CalTwoOp( postfixTokenList.at( i ), 
                              stackValue[top-1], stackValue[top] ) ; 
      stackValue[top-1] = strCalValue ;
      top-- ;
    } // if
    else if ( postfixTokenList.at( i ) == "?" )
    {
      if ( stackValue[top-1] == "true" )
      {
        strCalValue = stackValue[top] ;
        stackValue[top-1] = strCalValue ;
        top-- ;

        while ( postfixTokenList.at( i ) != ":" )
          i++ ;
        
      } // if
      else
      {
        stackValue[top-1] = "" ;
        stackValue[top] = "" ;
        --top ;
        --top ;
      } // else
      // strCalValue = DealWithCondition( i, postfixTokenList, stackValue[top-1] ) ;
    } // else if
    else if ( postfixTokenList.at( i ) == "," )
      ;
    else if ( postfixTokenList.at( i ) == "@+" ||
              postfixTokenList.at( i ) == "@-" ||
              postfixTokenList.at( i ) == "!" )
    {
      strCalValue = DealWithSign( postfixTokenList.at( i ), stackValue[top] ) ;
      stackValue[top] = strCalValue ;
    } // else if
    else if ( postfixTokenList.at( i ) == "<"  || postfixTokenList.at( i ) == "<=" || 
              postfixTokenList.at( i ) == ">"  || postfixTokenList.at( i ) == ">=" )
    {
      strCalValue = ComprTwoOp( postfixTokenList.at( i ), 
                                stackValue[top-1], stackValue[top] ) ; 
      stackValue[top-1] = strCalValue ;
      top-- ;                               
    } // else if
    else if ( postfixTokenList.at( i ) == "&&" || 
              postfixTokenList.at( i ) == "||" )
    {
      strCalValue = BoolTwoOp( postfixTokenList.at( i ), 
                               stackValue[top-1], stackValue[top] ) ; 
      stackValue[top-1] = strCalValue ;
      top-- ;
    } // else if
    else if ( postfixTokenList.at( i ) == "==" || 
              postfixTokenList.at( i ) == "!=" )
    {
      strCalValue = EvalTwoOp( postfixTokenList.at( i ), 
                               stackValue[top-1], stackValue[top] ) ; 
      stackValue[top-1] = strCalValue ;
      top-- ;              
    } // else if
    else if ( postfixTokenList.at( i ) == "="  || 
              postfixTokenList.at( i ) == "+=" ||
              postfixTokenList.at( i ) == "-=" ||
              postfixTokenList.at( i ) == "*=" ||
              postfixTokenList.at( i ) == "/=" ||
              postfixTokenList.at( i ) == "%=" )
    {
      strCalValue = AssignValue( postfixTokenList.at( i ), 
                                 stackValue[top-1], stackValue[top] ) ;
      stackValue[top-1] = strCalValue ;
      top-- ;       
    } // else if
    else if ( postfixTokenList.at( i ) == ":" )
      ;
    else // save operand to stack
    {
      string strTemp = postfixTokenList.at( i ).substr( 0, 1 ) ;
      
      if ( strTemp == "#" )
      {
        strTemp = postfixTokenList.at( i ).substr( 1, postfixTokenList.size()-1 ) ;
        postfixTokenList.at( i ) = gMapVar[strTemp].tokenValue ;
      } // if
      
      stackValue[++top] = postfixTokenList.at( i ) ;
    } // else
  } // for
  
  strCalValue = stackValue[top] ;

  if ( gMapVar.find( strCalValue ) != gMapVar.end() )
    strCalValue = gMapVar[strCalValue].tokenValue ;

  return strCalValue ;
} // CalPostfixVal()

bool IsString( string str )
{
  string op1 = "\"" ;
  string op2 = "\'" ;

  size_t found_op1 = 0 ;
  size_t found_op2 = 0 ;

  found_op1 = str.find( op1 ) ;
  found_op2 = str.find( op2 ) ;

  if ( found_op1 != str.npos ) 
    return true ; 
  else if ( found_op2 != str.npos )
    return true ; 
  else
    return false ; 
} // IsString()

bool HaveEnter( string str )
{
  string op = "\\n" ;

  size_t found_op = 0 ;

  found_op = str.find( op ) ;

  if ( found_op != str.npos ) 
    return true ; 
  else
    return false ; 
} // HaveEnter()

string CalTwoOp( string op, string strLeft, string strRight ) 
// calculate the value of the left operand and the right operand
{ 
  string strValue = "" ;

  if ( IsString( strLeft ) || IsString( strRight ) )
  {
    if ( IsString( strLeft ) )
      strLeft = strLeft.substr( 1, strLeft.length()-2 ) ;
    if ( IsString( strRight ) )
      strRight = strRight.substr( 1, strRight.length()-2 ) ;

    if ( strLeft == "\\n" )
      strValue = "\n" + strRight ;
    else if ( strRight == "\\n" )
      strValue = strLeft + "\n" ;
    else if ( strLeft == "\\n" && strLeft == "\\n" )
      strValue = "\n\n" ;
    else if ( HaveEnter( strLeft ) || HaveEnter( strRight ) )
    {
      if ( HaveEnter( strLeft ) )
      {
        string strTemp = "" ;

        for ( int i = 0 ; i <= strLeft.length()-2 ; i++ )
        {
          if ( strLeft.substr( i, i+1 ) == "\\n" )
          {
            strTemp = strLeft.substr( 0, i ) ;
            strLeft = strLeft.substr( i+2, strLeft.length()-1 ) ;
            strLeft = strTemp + "\n" + strLeft ;
          } // if
        } // for
      } // if

      if ( HaveEnter( strRight ) )
      {
        string strTemp = "" ;

        for ( int i = 0 ; i <= strRight.length()-2 ; i++ )
        {
          if ( strRight.substr( i, i+1 ) == "\\n" )
          {
            strTemp = strRight.substr( 0, i ) ;
            strRight = strRight.substr( i+2, strLeft.length()-1 ) ;
            strRight = strTemp + "\n" + strRight ;
          } // if
        } // for
      } // if

      strValue = strLeft + strRight ;
    } // else if
    else 
      strValue = strLeft + strRight ;

    strValue = "\"" + strValue + "\"" ;
  } // if
  else
  {
    int iLeft = atoi( strLeft.c_str() ) ;
    int iRight = atoi( strRight.c_str() ) ;
    int iValue = 0 ;

    if ( op == "+" )
      iValue = iLeft + iRight ;
    else if ( op == "-" )
      iValue = iLeft - iRight ; 
    else if ( op == "*" )
      iValue = iLeft * iRight ; 
    else if ( op == "/" )
      iValue = iLeft / iRight ;
    else if ( op == "%" )
      iValue = iLeft % iRight ;
    else if ( op == ">>" )
      iValue = iLeft >> iRight ;
    else if ( op == "<<" )
      iValue = iLeft << iRight ;

    stringstream intToString ; // type conversion
    intToString << iValue ;    // int
    intToString >> strValue ;  // string
  } // else

  return strValue;
} // CalTwoOp()

string ComprTwoOp( string op, string strLeft, string strRight )
// compares the value of the left-hand calculation with the right-hand
{
  double dLeft = atof( strLeft.c_str() ) ;
  double dRight = atof( strRight.c_str() ) ;

  if ( op == ">" ) 
  {
    if ( dLeft > dRight )
      return "true" ;
  } // if
  else if ( op == "<" ) 
  {
    if ( dLeft < dRight )
      return "true" ;
  } // else if
  else if ( op == ">=" ) 
  {
    if ( dLeft >= dRight )
      return "true" ;
  } // else if
  else if ( op == "<=" ) 
  {
    if ( dLeft <= dRight )
      return "true" ;
  } // else if

  return "false" ;
} // ComprTwoOp()

string BoolTwoOp( string op, string strLeft, string strRight )
{
  if ( op == "&&" )
  {
    if ( strLeft == "false" || strRight == "false" )
      return "false" ;
  } // if
  else if ( op == "||" )
  {
    if ( strLeft == "false" && strRight == "false" )
      return "false" ;
  } // else if

  return "true" ;
} // BoolTwoOp()

string EvalTwoOp( string op, string strLeft, string strRight )
{
  if ( op == "==" )
  {
    if ( strLeft == strRight )
      return "true" ;
  } // if
  else if ( op == "!=" )
  {
    if ( strLeft != strRight )
      return "true" ;
  } // else if 

  return "false" ;
} // EvalTwoOp()

string AssignValue( string op, string strLeft, string strRight )
// assign the value for gMapVer
{
  string strValue = "" ;

  if ( op == "=" )
  {
    gMapVar[strLeft].tokenValue = strRight ;
    strValue = strRight ;
  } // if
  else 
  {
    if ( IsString( strRight ) )
    {
      strValue = gMapVar[strLeft].tokenValue.substr( 1, gMapVar[strLeft].tokenValue.length()-2 ) ;
      strRight = strRight.substr( 1, strRight.length()-2 ) ;
      strValue = strValue + strRight ;
      strValue = "\"" + strValue + "\"" ;
      gMapVar[strLeft].tokenValue = strValue ;
    } // if
    else
    {
      int iLeft = atoi( gMapVar[strLeft].tokenValue.c_str() ) ;
      int iRight = atoi( strRight.c_str() ) ;

      if ( op == "+=" )
        iLeft = iLeft + iRight ;
      else if ( op == "-=" )
        iLeft = iLeft - iRight ;
      else if ( op == "*=" )
        iLeft = iLeft * iRight ;
      else if ( op == "/=" )
        iLeft = iLeft / iRight ;
      else if ( op == "%=" )
        iLeft = iLeft % iRight ;

      stringstream intToString ; // type conversion
      intToString << iLeft ;    // int
      intToString >> strValue ;  // string

      gMapVar[strLeft].tokenValue = strValue ;
    } // else
  } // else 

  return strValue ;
} // AssignValue()

string DealWithSign( string op, string value )
{
  string strValue = "" ;

  if ( op == "!" )
  {
    if ( value == "true" )
      strValue = "false" ;
    else
      strValue = "true" ;
  } // if
  else if ( op == "@+" )
    strValue = value ;
  else if ( op == "@-" )
  {
    int iTemp = atoi( value.c_str() ) ;
    iTemp = - ( iTemp ) ;

    stringstream intToString ; // type conversion
    intToString << iTemp ;    // int
    intToString >> strValue ;  // string    
  } // else if

  return strValue ;
} // DealWithSign()

void ReorganizeTokenList( vector<LabelOfToken>& tempTokenList )
{
  for ( int i = 0 ; i < gTokenList.size() ; i++ )
  {
    if ( gTokenList.at( i ).tokenValue == "[" )
    {
      tempTokenList.pop_back() ;
      string arrayName = gTokenList.at( i-1 ).tokenValue ;

      arrayName = arrayName + gTokenList.at( i ).tokenValue +
                  gTokenList.at( i+1 ).tokenValue + gTokenList.at( i+2 ).tokenValue ;
      
      i = i + 2 ; // ]
      gTokenList.at( i ).tokenValue = arrayName ;
      gTokenList.at( i ).tokenType = IDENT ;
    } // if
    
    tempTokenList.push_back( gTokenList.at( i ) ) ;
  } // for
} // ReorganizeTokenList()

string DealWithCondition( int& i, vector<string>& postfixTokenList, string boolOfEXE )
{
  string strValue = "" ;
  vector<string> splitPostfixList ;

  i++ ; // ?

  if ( boolOfEXE == "true" ) // execute form ? to :
  {
    while ( postfixTokenList.at( i ) != ":" )
    {
      splitPostfixList.push_back( postfixTokenList.at( i ) ) ;
      i++ ;
    } // while

    strValue = CalPostfixVal( splitPostfixList ) ;

    while ( postfixTokenList.at( i ) != "$"  &&
            postfixTokenList.at( i ) != "="  &&
            postfixTokenList.at( i ) != "+=" &&
            postfixTokenList.at( i ) == "-=" &&
            postfixTokenList.at( i ) == "*=" &&
            postfixTokenList.at( i ) == "/=" &&
            postfixTokenList.at( i ) == "%=" ) 
      i++ ;

    if ( postfixTokenList.at( i ) == "$" )
      i++ ; // $
  } // if
  else // execute from : to the end
  {
    while ( postfixTokenList.at( i ) != ":" ) 
      i++ ;
    
    while ( postfixTokenList.at( i ) != "$"  &&
            postfixTokenList.at( i ) != "="  &&
            postfixTokenList.at( i ) != "+=" &&
            postfixTokenList.at( i ) == "-=" &&
            postfixTokenList.at( i ) == "*=" &&
            postfixTokenList.at( i ) == "/=" &&
            postfixTokenList.at( i ) == "%=" ) 
    {
      splitPostfixList.push_back( postfixTokenList.at( i ) ) ;
      i++ ;
    } // while

    strValue = CalPostfixVal( splitPostfixList ) ;

    if ( postfixTokenList.at( i ) == "$" )
      i++ ;
  } // else

  return strValue ; 
} // DealWithCondition()

void AddConEndOP( vector<LabelOfToken>& splitTokenList )
{
  bool isEndCond = false ;

  for ( int i = 0 ; i < splitTokenList.size() ; i++ )
  {
    if ( splitTokenList.at( i ).tokenValue == ":" )
      isEndCond = true ;

    if ( isEndCond && 
         i == splitTokenList.size()-1 && 
         splitTokenList.at( i ).tokenValue == ")" ) 
      splitTokenList.at( i ).array_size = "000" ; 
    else if ( isEndCond && 
              i != splitTokenList.size()-1 && 
              splitTokenList.at( i ).tokenValue == ")" &&
              splitTokenList.at( i+1 ).tokenType == OP )
      splitTokenList.at( i ).array_size = "000" ; 
  } // for
} // AddConEndOP()

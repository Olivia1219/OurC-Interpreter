# C語言直譯器

## 目的
透過撰寫C語言之直譯器來訓練程式語言，並透過處理大量的函式來訓練邏輯思維以及統整處理大量程式碼的能力

## 功能
主要分成了三大部分Scanner、Parser、Evaluator
* Scanner
  * 將input字符串切分成符合語法的token串
  * 如有錯誤(Lexical Error)則會輸出不符合token語法規定之信息
* Parser
  * 由OurC的BNF撰寫語法判斷
  * 如有錯誤(Syntax Error)則會輸出不符合BNF語法規定之信息
* Evaluator
  * 執行運算input所要執行的C語言指令
  * 如有錯誤(Semantic Error)則會輸出導致運算出問題之信息

## 使用方法
* 可以宣告變數以及函式
* 可以輸入之型別
  * int
  * char
  * float
  * string
  * bool
* 可以對已宣告變數進行運算，可使用的運算子如下
  * =、+=、-=、*=、/=、%=
  * &&、||、!、==、!=
  * <、>、<=、>=
  * <<、>>
  * +、-、*、/、%
  * ? :
* 可以使用 cout 與以下的內建指令函式
  * ListAllVariables() : 印出所有宣告之變數名稱
  * ListAllFunctions() : 印出所有宣告之函式名稱
  * ListVariable("指定之變數名稱") : 可印出其指定變數之宣告
  * ListFunction("指定之函式名稱") : 可印出指定函式之完整宣告內容
  * Done() : 程式執行結束

## 待解決的問題
* while的運算
* if-else的判斷運算

## 簡述專案使用到的技術
* C/C++
* 資料結構與演算法

## 達成成果
<video src="影片檔案網址" controls></video>













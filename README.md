# OurC Interpreter
## C語言直譯器

###### 目的
透過撰寫C語言之直譯器來訓練程式語言，並透過處理大量的函式來訓練邏輯思維以及統整處理大量程式碼的能力

###### 功能
主要分成了三大部分Scanner、Parser、Evaluator
* Scanner
將input字符串切分成符合語法的token串
如有錯誤(Lexical Error)則會輸出不符合token語法規定之信息
* Parser
由OurC的BNF撰寫語法判斷
如有錯誤(Syntax Error)則會輸出不符合BNF語法規定之信息
* Evaluator
執行運算input所要執行的C語言指令
如有錯誤(Semantic Error)則會輸出導致運算出問題之信息



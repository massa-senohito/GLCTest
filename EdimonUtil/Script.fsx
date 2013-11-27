// F# の詳細については、http://fsharp.net を参照してください。F# プログラミングのガイダンスについては、
// 'F# チュートリアル' プロジェクトを参照してください。

#load "Library1.fs"
open EdimonUtil

// ここでライブラリ スクリプト コードを定義します
let className="FragmentStrategy" //"VertexStrategy" // "EffectStrategy"
let privatemember=[""]|>List.reduce (+)
type MemberType={
  RetType:string
  Name:string
  RecType:string
  }
  with
  member t.cl=t.RetType + " " + t.Name + t.RecType + ";\n"
  member t.h cln= t.RetType + " " + cln + "::" + t.Name + t.RecType + "\n"
let mem ret n re={RetType=ret;Name=n;RecType=re}
let publicMember=
  [
  mem "void" "BindEnable" "(Types::action)"
  mem "void" "SendTextureToFlagment" "(Types::str,int)"
  ]
let toh ml cln=ml|>Seq.map(fun (i:MemberType)->i.h cln + " ")|>Seq.reduce (+)
let tocl ml=ml|>Seq.map(fun (i:MemberType)->i.cl + " ")|>Seq.reduce (+)
let cppClassBuilder =
  "class " + className + "{\n" + privatemember 
  + "public:\n" + (tocl publicMember) + "\n};"
let cppHBuilder=
  toh publicMember className
cppHBuilder
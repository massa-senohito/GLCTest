//探す部分、コピーする作業が増えてきてミスが出るかもしれない
//＞powershellかfsで作業用スクリプトを書く
//let jobs=[cplibs;cpheadder]
//余力があったらcgcするものも>エフェクトはcgcいらない？
//#r ""

type Paths=
  |Full of string
  |File of string
let filename=function
  |(File(x),_)->x
  |_->"err"
let libdest= @"C:\Users\massa_senohito\Documents\Visual Studio 11\Projects\GLCTest\lib\"
let libsrc = @"C:\Users\massa_senohito\Documents\Visual Studio 11\Projects\CgGLRap\Debug\"
let hdsrc  = @"C:\Users\massa_senohito\Documents\Visual Studio 11\Projects\CgGLRap\CgGLRap\"
let hddest = @"C:\Users\massa_senohito\Documents\Visual Studio 11\Projects\GLCTest\include\"
//glewいれてcgの様子を見たい
let slsrc  = @"C:\Users\massa_senohito\Documents\Visual Studio 11\Projects\GLCTest\GLCTest\"
let sldest = @"C:\Users\massa_senohito\Documents\Visual Studio 11\Projects\GLCTest\Debug\"
let toFile =Seq.map File
let libs=["CgGLRap.lib"]|>toFile
let hs=["TypeUtil.h";"CgLoader.h";"EffectStrategy.h"] |>toFile
let sls=["bumpdemo.cgfx"] |>toFile //shaders

let ps x=printfn "%s" x
let cp src dest=
  match src,dest with
  |(Full(s),Full(d))->System.IO.File.Copy(s,d,true)
  |_->()
let read f=
  System.IO.File.ReadAllText f|>ps
let concPath dir=function
  |File(f)->Full(dir+f)
  |_->File ""
let hsl=
  hs|>Seq.map (fun s->concPath hdsrc s,concPath hddest s) 
let lil= //lib list
  libs|>Seq.map (fun l->concPath libsrc l,concPath libdest l)
let sll=
  sls|>Seq.map(fun s->concPath slsrc s,concPath sldest s)
let testr xs=
  Seq.iter ps xs
let cpall xs=
  xs |>Seq.iter (fun h->cp (fst h) (snd h))
//testr hsl;;
cpall hsl;;
cpall lil;;
cpall sll;;
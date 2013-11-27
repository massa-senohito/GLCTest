namespace EdimonUtil
module ScriptLoader=
  open System.Runtime.InteropServices
  open System.IO
//http://www.asahi-net.or.jp/~kv8s-yjm/another/yja108.htm
//C++でcomオブジェクトを呼び出す
  type ProcInfo=System.Diagnostics.ProcessStartInfo
  type Proc=System.Diagnostics.Process
  type Assem=System.Reflection.Assembly

  type IPlugin=
    abstract member Init:unit->unit
    abstract member Destroy:unit->unit
    abstract member Version:int
    abstract member Name:string
//同じアセンブリの別バージョンを読むとキャストなどで問題が発生する
  let mutable AssemList:IPlugin list=[]
  let change =
    new FileSystemWatcher(".","*.lua")
  let splitExt (file:string)=
    file.Split('.').[0]
  let OnChange (watcher:FileSystemWatcher) fileF=
    watcher.Changed.Add(fun e->fileF e.FullPath e.Name;())//must be class
  let moonCompile filePath name=
    let moon=ProcInfo("moonscript",filePath)
    "エラーがでても実行しているluaをアンバインドし"
  let monoCompile filePath name=
    let monoCom=ProcInfo("mono",filePath)//fsc
    let monoP=Proc.Start(monoCom)
    monoP.WaitForExit()
    Assem.LoadFile(splitExt name)
  let injectAssem (assem:Assem)=
    AssemList<- ( assem.CreateInstance("IPlugin"):?> IPlugin)::AssemList
    ()

  let OnChangeFs w=OnChange w (fun f n->monoCompile f n|>injectAssem)
  [<Guid("31CCA209-3FB5-4381-B3E1-C8B7B653C93A")>]
  type IListMes=
    abstract member Add:int->unit
    abstract member Init:unit->unit
  [<ClassInterface(ClassInterfaceType.AutoDispatch)>]
  [<ProgId("EdimonUtil.ScriptLoader.Class1")>]
  [<Guid("86D52FBF-3665-44FD-88D3-A2792992B0FD")>]
  type Class1() = 
    interface IListMes with
      member t.Add i=printfn "%d" i
      member t.Init()=printfn "%s" "hellocom"
    member t.X = "F#"

#include "stdafx.h"
class StackableState;
class SceneStack{
    //if(cancelled)popscene
    void OnSelected(int ID){}
    void OnCalcelled(int curScene){}
    //void selectScene(Types::SelectScene,Types::CancelScene){
      //callback(cur)
    //}
};
class SceneTree{
  //destroyScene(prevScene)
  //update=nextScene->update
};
/* let dispatchStackSeq curScr=
       |OnMap,OpenSubMenu->
       |SubMenu,OpenItem->
  let findtable =function
    |Route1->[mem;]
    
  let dispatchTreeSeq curScr=
       |OnMap(place,flags),EnterBattle->
         let table=findtable(place);
         startBattle (randOne table)
       |OnBattlen
*/
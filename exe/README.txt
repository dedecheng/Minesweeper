(GUI模式尚未完成)

執行方式:
	-直接開啟MineSweeper.exe可進入GUI模式
	-也可開啟終端介面，選擇遊玩的模式:
		-指令檔模式 : MineSweeper.exe CommandFile <輸入指令檔> <輸出檔>
		-輸入指令模式 : MineSweeper.exe CommandInput
		-GUI模式 : MineSweeper.exe GUI

規則:
	-玩家需透過揭開方塊，避免踩到地雷，同時藉由周圍的數字推測哪些方塊為地雷
 	，直到所有空白方塊都被開啟就為獲勝，踩到地雷就算失敗。
	-每格的數字代表其9宮格內含有的炸彈數量
	-玩家可以放置旗幟或問號來輔助判斷

指令(指令檔和輸入指令模式):
-Load
	-載入盤面檔:Load BoardFile <盤面檔相對路徑>
	-指定地雷數量:Load RandomCount <M> <N> <炸彈數量>
	-指定地雷生成機率:Load RandomRate <M> <N> <炸彈生成機率>
-StartGame
	-成功載入盤面後，才可開始遊戲
-Print
	-印出遊玩中的2D盤面:Print GameBoard
	-印出現在遊戲狀態 :Print GameState
	-印出解答的2D盤面:Print GameAnswer
	-總炸彈數量:Print BombCount
	-當前標註的總旗幟數量:Print FlagCount
	-當前打開的空白格子數:Print OpenBlankCount
	-當前尚未打開的空白格子數:Print RemainBlankCount
-LeftClick
	-開啟格子:LeftClick <row> <col>
-RightClick
	-第一次右鍵標註旗幟，第二次右鍵標註問號，第三次右鍵回復無標註
	-標註旗幟/問號:RightClick <row> <col>
-Replay
	-在遊戲結束後，重新進行新一輪的遊戲
-Quit
	-在遊戲結束後，關閉整個程式


其他:
-盤面檔格式:
	-M為Row的數量，N為Column的數量
	-格式:
	 <M> <N>
	 2D盤面，O表示無地雷，X表示地雷
-輸出格式
	-<指令> : Success/Failed
	-當遊戲獲勝或失敗時，You win/lose the game




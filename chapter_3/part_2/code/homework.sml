(* 3.8 (a) *)
fun len ([],count) = count | len(L, count) = len(tl(L),count+1);

fun tailLen(L) = len(L,0);

(* 3.8 (b) *)
fun max (L,m) =
	if L=nil then m
	else if hd(L) > m then max(tl(L),hd(L))
	else max(tl(L),m);
	
fun min(L,m) =
	if L=nil then m
	else if m > hd(L) then min(tl(L), hd(L))
	else min(tl(L),m);
	
fun find_min_max(L) = [min(L,hd(L)),max(L,hd(L))];

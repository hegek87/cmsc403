open TextIO;

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

(* 3.8 (c) *)

fun getInput() = 
	let 	val y = inputLine(stdIn)
		val x = substring(valOf y,0,size(valOf y)-1)
		val z = valOf(Int.fromString x)
	in 
		if z = 0 then [] else z::getInput()
	end;
	
(* 3.8 (d) *)
fun printList(nil) = ()
|	printList(x::xs) = (
		print(Int.toString(x));
		print("\n");
		printList(xs)
	);
	
fun findMaxMinInput() = 
	let val x = getInput()
	in
		printList x;
		find_min_max x
	end;
	
(* 3.8 (h) *)
fun twice f = fn x => f(f(x));
fun square x = x*x;

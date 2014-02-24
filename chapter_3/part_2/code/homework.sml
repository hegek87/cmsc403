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
	
(* 3.8 (e) *)
(* quick sort. We take the first element is a pivot and partition the set based on this first element, then we will recursively call quicksort on the two halves *)
fun 	partition piv f b [] = (f,b) |
	partition piv f b (x::xs) =
		if piv > x then partition piv (x::f) b xs
		else partition piv f (x::b) xs;
		
fun 	quicksort [] = [] |
	quicksort (x::xs) =
		let val (front, back) = partition x [][] xs
		in
			quicksort front @ [x] @ quicksort back
		end;
				

(* 3.8 (f) *)
fun 	merge l1 [] = l1 |
	merge [] l2 = l2 |
	merge (x::xs) (y::ys) = 
		if x > y then y::merge (x::xs) ys
		else x::merge xs (y::ys);
		
fun len [] = 0 | len (x::xs) = 1 + len xs;

fun 	mergesort [] = [] |
	mergesort (x::[]) = [x] |
	mergesort lis =
		let 	val mid = len lis div 2
			val front = List.take(lis, mid)
			val back = List.drop(lis, mid)
		in
			merge (mergesort front) (mergesort back)
		end;
		

	
	
(* 3.8 (h) *)
fun twice f = fn x => f(f(x));
fun square x = x*x;

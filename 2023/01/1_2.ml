open Core

let nums = [|"one";"two";"three";"four";"five";"six";"seven";"eight";"nine"|]
let calculate fp =
	let parse_line l =
		let rec scan s i di n =
			if i = String.length s || i = -1 then n
			else if Char.is_digit s.[i] then Char.to_int s.[i] - 48
			else match
				Array.findi nums ~f:(fun _ name -> String.is_substring_at s ~pos:i ~substring:name)
			with
			| Some (v, _) -> v + 1
			| None -> scan s (i + di) di n
		in (scan l 0 1 0) * 10 + (scan l (String.length l - 1) (-1) 0)
	in In_channel.fold_lines ~f:(fun acc l ->
		let v = parse_line l in
		Printf.printf "%d %s\n" v l; acc + v) ~init:0 fp

let () =
	let fp = In_channel.create "t_c.txt" in
	Printf.printf "%d\n" @@ calculate fp;
	In_channel.close fp

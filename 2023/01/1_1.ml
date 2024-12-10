open Core

let calculate fp =
	let parse_line l =
		let d = String.filter l ~f:Char.is_digit in
		(Char.to_int d.[0] - 48) * 10 + (Char.to_int d.[String.length d - 1] - 48)
	in In_channel.fold_lines ~f:(fun acc l -> acc + parse_line l) ~init:0 fp

let () =
	let fp = In_channel.create "1.txt" in
	Printf.printf "%d\n" @@ calculate fp;
	In_channel.close fp

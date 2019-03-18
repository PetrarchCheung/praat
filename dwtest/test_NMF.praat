# test_NMF.praat
# djmw 20190312

appendInfoLine: "test_NMF.praat"

appendInfoLine: tab$, "Simple interface test"
@test_simple
appendInfoLine: tab$, "Diagonals "
@test_diagonal

appendInfoLine: "test_NMF.praat OK"

procedure test_simple
	for .i to 10
		.ncol = 10
		.nrow = randomInteger (1, 100)
		.nfeatures = randomInteger(1,5)
		.mat = Create simple Matrix: "xy", .nrow, .ncol, "randomUniform (1,10)"
		.nmf = To NMF: .nfeatures, 500, 1e-09, 1e-09, "RandomUniform"
		plusObject: .mat
		.dist = Get Euclidean distance
		Improve factorization: 10, 1e-09, 1e-09
		.dist2 = Get Euclidean distance
		assert .dist2 <= .dist
		appendInfoLine: tab$, tab$, .nrow, "x", .ncol, ", aprox = ", .nfeatures, " 2-norm=", .dist2
		removeObject: .mat, .nmf
	endfor
endproc

procedure test_diagonal
	for .i  to 10
		.ncol = .i + 1
		.nrow = .ncol
		.nfeatures = .ncol - 1 
		.mat = Create simple Matrix: string$(.nrow)+"x"+string$(.ncol), .nrow, .ncol, "if row = col then randomUniform(0,10) else 0 fi"
		.nmf = To NMF: .nfeatures, 1000, 1e-09, 1e-09, "RandomUniform"
		plusObject: .mat
		.dist = Get Euclidean distance
		appendInfoLine: tab$, tab$, .nrow, "x", .ncol, ", aprox = ", .nfeatures, " 2-norm=", .dist
		removeObject: .mat, .nmf
	endfor
endproc

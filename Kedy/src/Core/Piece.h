#pragma once

namespace Kedy {

	enum BufferType { ORIGINAL, ADD };


	struct Piece {

		BufferType bufferType;
		int start;
		int length;

		Piece(BufferType type, int start, int len)
			: bufferType(type), start(start), length(len) {}

	};
}

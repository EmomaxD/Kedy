#pragma once

namespace Kedy {

	enum BufferType { ORIGINAL, ADD };


	struct Piece {

		BufferType bufferType;
		size_t start;
		size_t length;

		Piece(BufferType type, size_t start, size_t len)
			: bufferType(type), start(start), length(len) {}

	};
}

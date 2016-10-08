//  Node.js script to convert Arduino output into a JPEG file.
"use strict";
const data = [
////  Begin


//Initializing camera....
//Camera initialization done.
//Precapture...
//Capture...
//picTotalLen:2276
//GetData...
"ff d8 ff db 00 84 00 14 0e 0f 12 0f 0d 14 12 10 12 17 15 14 18 1e 32 21 1e 1c 1c 1e 3d 2c 2e 24 32 49 40 4c 4b 47 40 46 45 50 5a 73 62 50 55 6d 56 45 46 64 88 65 6d 77 7b 81 82 81 4e 60 8d 97 8c 7d 96 73 7e 81 7c 01 15 17 17 1e 1a 1e 3b 21 21 3b 7c 53 46 53 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c ",
"7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c 7c ff c0 00 11 08 00 78 00 a0 03 01 21 00 02 11 01 03 11 01 ff dd 00 04 00 0a ff c4 01 a2 00 00 01 05 01 01 01 01 01 01 00 00 00 00 00 00 00 00 01 02 03 04 05 06 07 08 09 0a 0b 10 00 02 01 03 03 02 04 03 05 05 04 04 00 00 01 7d 01 02 03 00 04 11 05 12 21 31 41 06 13 51 61 07 22 71 14 32 81 91 a1 08 23 42 b1 c1 15 52 d1 f0 24 ",
"33 62 72 82 09 0a 16 17 18 19 1a 25 26 27 28 29 2a 34 35 36 37 38 39 3a 43 44 45 46 47 48 49 4a 53 54 55 56 57 58 59 5a 63 64 65 66 67 68 69 6a 73 74 75 76 77 78 79 7a 83 84 85 86 87 88 89 8a 92 93 94 95 96 97 98 99 9a a2 a3 a4 a5 a6 a7 a8 a9 aa b2 b3 b4 b5 b6 b7 b8 b9 ba c2 c3 c4 c5 c6 c7 c8 c9 ca d2 d3 d4 d5 d6 d7 d8 d9 da e1 e2 e3 e4 e5 e6 e7 e8 e9 ea f1 f2 f3 ",
"f4 f5 f6 f7 f8 f9 fa 01 00 03 01 01 01 01 01 01 01 01 01 00 00 00 00 00 00 01 02 03 04 05 06 07 08 09 0a 0b 11 00 02 01 02 04 04 03 04 07 05 04 04 00 01 02 77 00 01 02 03 11 04 05 21 31 06 12 41 51 07 61 71 13 22 32 81 08 14 42 91 a1 b1 c1 09 23 33 52 f0 15 62 72 d1 0a 16 24 34 e1 25 f1 17 18 19 1a 26 27 28 29 2a 35 36 37 38 39 3a 43 44 45 46 47 48 49 4a 53 54 55 ",
"56 57 58 59 5a 63 64 65 66 67 68 69 6a 73 74 75 76 77 78 79 7a 82 83 84 85 86 87 88 89 8a 92 93 94 95 96 97 98 99 9a a2 a3 a4 a5 a6 a7 a8 a9 aa b2 b3 b4 b5 b6 b7 b8 b9 ba c2 c3 c4 c5 c6 c7 c8 c9 ca d2 d3 d4 d5 d6 d7 d8 d9 da e2 e3 e4 e5 e6 e7 e8 e9 ea f2 f3 f4 f5 f6 f7 f8 f9 fa ff da 00 0c 03 01 00 02 11 03 11 00 3f 00 e3 28 a4 05 9b 71 e7 44 f0 7f 17 de 4f ae 39 ",
"15 5e 80 0a 55 3b 58 1a 00 b2 58 11 51 b5 00 30 d3 68 00 a2 80 0a 28 01 28 a0 02 8a 00 28 a0 0f ff d0 e3 28 a4 03 e1 90 c5 32 48 bd 54 83 52 5e 22 a5 d4 82 32 0a 13 b9 71 e8 79 1f ce 80 20 a5 14 00 e0 c4 52 ee a0 04 a4 a0 02 8a 00 28 a0 02 8a 00 28 a0 04 a2 80 3f ff d1 e3 28 a4 01 4b 40 06 29 68 00 a2 80 0a 28 00 a2 80 0a 5a 00 4a 28 00 a2 80 0a 4a 00 ff d2 e3 29 ",
"69 00 a0 51 40 0b 45 00 18 a4 a0 02 8a 00 5a 28 00 a2 80 0a 28 01 28 a0 02 8a 00 ff d3 c1 1a 52 7f cf 51 4a 34 91 ff 00 3d 45 07 47 b2 5d c5 fe c8 3d a4 aa f7 56 26 dc 03 b8 1a 2c 44 e9 f2 ab 95 82 12 40 ab d1 e9 32 c8 81 83 0a 42 85 3e 64 2f f6 34 fd 8a 9a 69 d1 ee 07 60 69 95 ec 58 d3 a4 dc ff 00 73 34 d3 a6 5c 8f f9 67 f9 50 2f 65 21 86 c2 e0 7f cb 33 4d 36 93 ",
"8e b1 b5 16 27 d9 cb b0 d3 04 a3 aa 1f ca 9a 63 71 d5 4f e5 48 4e 2d 0d da 47 50 69 28 24 29 28 00 a2 80 3f ff d4 c4 16 52 67 ef 9f ce 96 ea ce 6b 78 bc cf 30 91 5b ca 95 88 55 6e 52 13 c8 3f 8c d2 34 ae e3 e6 62 6b 13 46 db 10 55 84 bd 9d 06 15 f8 a4 38 c9 c7 62 41 a9 5c 0f e2 a7 8d 52 71 e8 69 dc bf 6a c7 0d 5a 61 d4 03 4e 1a bb f7 41 40 fd ab 1e 35 83 de 3a 70 ",
"d5 d0 f5 8e 8d 0a f6 c2 ff 00 69 c2 7e f4 7f a5 2f db ed 4f 54 1f 95 3b 0d 55 41 f6 9b 26 ea a3 f2 a6 93 62 fd 96 95 8a e6 83 1a 6d ec 5b a6 29 86 c6 d1 ba 30 14 58 5c b0 65 3b db 38 a1 50 63 6c e6 a9 6d a4 d1 cf 24 93 d0 ff d5 67 90 81 f1 9a b1 71 6c 24 b7 28 79 18 ae b9 36 ce 4d a3 a1 81 3d 86 32 53 b7 6a a2 c8 50 e1 85 72 9a d2 a9 ce 84 c5 2e 29 1b 06 29 71 40 ",
"06 28 c5 00 18 ab 16 11 89 2f 23 46 e8 73 fc a8 03 a5 b8 d3 61 f2 86 10 74 f4 aa 0d a6 c5 d8 0a ed a7 14 e3 a9 c6 e6 e2 c6 a6 91 1b b0 14 dd 47 48 4b 6b 73 22 54 ce 0a e6 91 a8 de e6 1f 22 8c b7 a9 ae 53 a0 42 49 ea 73 4d a4 07 ff d6 b2 f6 c2 46 0c a6 ac 22 61 30 6b a1 ca ea c7 37 2d 8a b7 16 ca 41 65 ea 2b 1a fe d4 14 2e a3 91 58 c9 59 98 c7 f7 75 17 66 65 e2 8c ",
"52 3b cb d6 b6 02 e2 12 e5 f6 f3 81 53 1d 1c e4 62 41 d3 9a 57 13 65 78 74 e9 67 9d e2 4f e0 ea 7b 54 53 5a c9 04 de 53 af cd db de 9f 70 b9 38 d2 6e 8a 6e d8 07 b1 3c d3 2d 51 a0 bf 88 3a 90 77 81 cd 2d d0 5c ed d6 30 f1 29 3d c5 55 9a 38 d5 b1 c5 76 53 6e c7 24 ac 3e 18 10 fc c2 a3 d4 63 0d 06 d3 d2 89 3d 49 9e 90 d0 e7 6e 74 e5 23 28 2b 25 d0 a3 10 6b 91 9a d0 ",
"ab ce ac c6 52 52 3a 4f ff d7 a3 a6 6a c5 17 cb 98 e7 de b6 12 ed 64 15 8b 94 a1 3b f4 37 f6 4a a4 2e 87 19 93 61 03 92 6b 36 ec 85 85 b7 7a 55 ba bc d2 31 ad 86 b5 34 fa a3 00 f5 34 56 82 1c b2 3a 02 15 88 07 ad 4a b7 73 a9 c8 91 a8 15 8d bd 04 f9 70 49 70 fd 49 ef df 15 6c c7 15 c4 f1 5c 8e 40 c9 15 29 ee c1 ef 72 a6 a7 7f 35 b5 da 2a 28 31 91 e9 d6 9d a9 c4 99 ",
"b7 98 0c 7c eb f9 55 75 b1 3d 13 37 2d e4 53 0a 8c 8e 95 14 d0 6e 6c 8a e9 a7 2b 1c f2 8d c7 c0 9e 5a e2 89 b6 b0 c3 77 a6 f5 60 d5 d5 8c ab 98 c4 72 10 3a 56 2e a7 12 8f 98 0a e6 66 14 6f 1a 96 33 29 2a 4f 48 ff d0 e5 aa cc 37 b2 c5 c6 72 2a 65 15 25 a9 a4 2a 38 3d 0b 63 55 20 74 e6 ab 5c de bc fc 1e 05 4c 69 d9 dc ba 95 b9 95 91 5b 34 b9 ad 0c 03 34 53 02 c4 77 ",
"92 c7 01 89 4e 14 d4 b0 6a 52 c1 0f 94 bd 07 4a 04 5b 8b 59 18 1e 6c 64 91 dc 55 6b fd 49 ae f0 a0 6d 51 fa d0 b4 d4 56 d4 2d 35 39 e2 91 77 39 2a 38 ae 9a 1d 46 39 10 10 73 58 d5 9c 93 56 37 a7 4d 49 12 7d a5 58 75 c1 a6 f9 83 ab 1e 95 b5 3a de ee a6 4f 0e f9 8a 37 72 ef 6c 8a c5 d4 e6 07 0a 2a 63 2e 6b 99 55 a3 c9 59 33 32 92 99 a9 ff d1 c1 6b 36 5e a8 c3 f0 a2 ",
"1b 26 9a 50 88 79 3e b4 01 65 f4 2b a5 e8 01 a8 5b 4a bb 5e b1 1f c2 80 22 6b 29 d7 ac 4d f9 53 0c 4e bf 79 48 fc 28 01 bb 7d a8 db 40 06 28 c5 00 18 a3 14 00 98 ab 16 f7 4f 01 e0 f1 4a 4a ea c5 c2 6e 0e e6 94 5a 94 6c 3e 6e 2a 53 7f 0e 3a d7 3f b3 68 ec f6 b1 6a e5 3b ad 49 48 db 18 fc 6b 2d d8 bb 65 ab 68 47 95 1c 95 25 cf 2b 8c c5 26 2a cc cf ff d2 d9 30 a3 75 ",
"51 51 35 ac 41 b7 04 00 8e f5 22 26 04 6c 06 9c 36 9e a2 98 0e f2 e2 6e aa 29 0d ad bb f5 51 40 11 be 95 68 fd 63 5f ca a0 7d 02 d1 c7 08 07 d2 80 20 7f 0c db 9f ba 48 fc 6a 06 f0 b2 f3 b6 46 fc 68 b8 15 df c3 13 0f bb 27 e9 55 df c3 d7 6b d3 69 a7 70 b9 03 e8 d7 89 ff 00 2c f3 f4 35 0b e9 d7 49 d6 16 fc a8 0b 90 b5 b4 cb d6 36 1f 85 46 50 8e a0 d0 31 a4 7a d3 71 ",
"40 09 8a 31 40 1f ff d3 db dd 48 c7 22 a4 43 51 ba ad 39 5f 8f a5 30 10 4c 49 fb bc 54 aa e0 8e 28 01 d9 14 bb bd e8 10 be 66 3f 8a 94 4b e8 73 40 0b e6 9a 3c df 6a 00 0c 8a 7a 8f 5a 6b 18 cf 55 14 00 d6 8e 06 1f 74 54 4d 69 6c fd 51 69 88 81 f4 bb 47 cf ee d7 f2 a8 1f 43 b3 6f e0 03 e9 40 15 df c3 b6 c7 a6 47 e3 50 37 86 a3 fe 19 0d 03 b9 ff d4 d5 df 46 ea 42 23 ",
"2d b5 81 a7 ef c1 f6 34 00 a2 41 4e 0e 07 4a 00 76 fa 3c ca 00 86 e5 ce d0 46 6a 3d d2 1f bb c2 d0 c4 90 b2 4b 24 7f 77 26 84 ba 7e 7b e2 80 1e 2e 9b e5 ce 39 ed 52 49 38 42 07 52 68 01 bf 69 5c 73 c1 cf 4a 04 e8 46 73 8a 60 0b 2a b7 43 47 98 09 c0 6a 00 51 21 de 06 69 fb e8 03 ff d5 d3 52 ad d0 83 4b b6 a4 06 b2 64 53 61 04 e4 13 d2 98 89 76 1f 63 46 cf 55 a0 03 ",
"68 f7 a3 6f bd 00 2e cc fa 1a 36 9f 4a 00 36 fa 8a 36 2f a5 00 46 f0 29 60 47 18 34 b2 45 bb 0c a7 91 40 88 cd bb 67 71 39 6c e6 9a 6d cb 12 cc 3b 74 14 0a c3 0c 12 96 2c 0e 38 c0 a5 85 19 58 00 09 f5 cd 03 45 95 5c b9 a7 95 c0 a6 07 ff d9 ",
//Read 19 of 19
//Done



////  End
];
const combined_data = data.join("").split(" ").join("");
const bin = new Buffer(combined_data, "hex");
const fs = require("fs");
fs.writeFileSync("a.jpg", bin);


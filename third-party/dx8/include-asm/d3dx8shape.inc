ifndef __D3DX8SHAPES__

__D3DX8SHAPES__			equ	1


  D3DXCreatePolygon		Proto	:DWord, :DWord, :DWord, :DWord, :DWord
  D3DXCreateBox			Proto	:DWord, :DWord, :DWord, :DWord, :DWord, :DWord
  D3DXCreateCylinder		Proto	:DWord, :DWord, :DWord, :DWord, :DWord, :DWord, :DWord, :DWord
  D3DXCreateSphere		Proto	:DWord, :DWord, :DWord, :DWord, :DWord, :DWord
  D3DXCreateTorus		Proto	:DWord, :DWord, :DWord, :DWord, :DWord, :DWord, :DWord
  D3DXCreateTeapot		Proto	:DWord, :DWord, :DWord

  D3DXCreateTextA		Proto	:DWord, :DWord, :DWord, :DWord, :DWord, :DWord, :DWord
  D3DXCreateTextW		Proto	:DWord, :DWord, :DWord, :DWord, :DWord, :DWord, :DWord


endif

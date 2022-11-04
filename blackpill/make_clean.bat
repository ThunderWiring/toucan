del  .\\*.d
del  .\\*.o
del /q .\\out\\cpp_out\\*
del /q .\\out\\c_out\\*
del /q .\\out\\prog_out\\*
del /q .\\out\\lib\\*
del .\\out\\core
del /q .\\out\\*.*

@REM remove *.h.gch files since they cause internal error in make 
@REM (internal error in mingw32_gt_pch_use_address)
del /q .\\toucan\\cpp\\*.hpp.gch
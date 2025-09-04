for %%i in (Patches/*.obj) do (
    echo %%i
    BPE Patches\%%i Patches\%%~ni_comp_para_result.obj
    copy Patches\%%~ni_comp_para_result.obj Patches\Patch_Para
)
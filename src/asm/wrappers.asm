
	public _gui_PrintLine_wrapper

	extern _gui_PrintLine

_gui_PrintLine_wrapper:
	pop bc
	ex (sp),hl
	push bc
	jp _gui_PrintLine

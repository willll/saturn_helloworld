/****************************************
*			include files				*
****************************************/
#include	"per_x.h"

/****************************************
*		declare private objects			*
****************************************/
static trigger_t	GetTriggerDigital( const SysDevice	*device );
static trigger_t	GetTriggerAnalog( const SysDevice	*device );
static trigger_t	GetTriggerPointer( const SysDevice	*device );
static trigger_t	GetTriggerKeyboard( const SysDevice	*device );
static trigger_t	GetTriggerMD3B( const SysDevice	*device );
static trigger_t	GetTriggerMD6B( const SysDevice	*device );
static trigger_t	GetTriggerMDMouse( const SysDevice	*device );
static trigger_t	GetTriggerUnknown( const SysDevice	*device );

static trigger_handler_t	GetTrigger[] = {
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerDigital, GetTriggerDigital,
	GetTriggerDigital, GetTriggerDigital, GetTriggerDigital, GetTriggerDigital,
	GetTriggerDigital, GetTriggerDigital, GetTriggerDigital, GetTriggerDigital,
	GetTriggerDigital, GetTriggerDigital, GetTriggerDigital, GetTriggerDigital,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerAnalog, GetTriggerAnalog,
	GetTriggerAnalog, GetTriggerAnalog, GetTriggerAnalog, GetTriggerAnalog,
	GetTriggerAnalog, GetTriggerAnalog, GetTriggerAnalog, GetTriggerAnalog,
	GetTriggerAnalog, GetTriggerAnalog, GetTriggerAnalog, GetTriggerAnalog,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerPointer, GetTriggerPointer,
	GetTriggerPointer, GetTriggerPointer, GetTriggerPointer, GetTriggerPointer,
	GetTriggerPointer, GetTriggerPointer, GetTriggerPointer, GetTriggerPointer,
	GetTriggerPointer, GetTriggerPointer, GetTriggerPointer, GetTriggerPointer,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerKeyboard, GetTriggerKeyboard,
	GetTriggerKeyboard, GetTriggerKeyboard, GetTriggerKeyboard, GetTriggerKeyboard,
	GetTriggerKeyboard, GetTriggerKeyboard, GetTriggerKeyboard, GetTriggerKeyboard,
	GetTriggerKeyboard, GetTriggerKeyboard, GetTriggerKeyboard, GetTriggerKeyboard,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerMD3B, GetTriggerMD6B, GetTriggerMDMouse,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
	GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown, GetTriggerUnknown,
};

/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		#include	"per_x.h"											*
*																		*
*		PER_SetTriggerHandler( id, handler );							*
*																		*
*		?w?????h?c???????y???t?F?????p???g???K?n???h???????????????B	*
*																		*
*				?E?E?E?E?E												*
*		?????????u?w?????h?c???????f?o?C?X?p???n???h?????????????????v	*
*		?????????????????????????????B?u?w?????^?C?v?v??????????????	*
*		?????A?????????????????B										*
*																		*
*		???????????????????i?n???h???j???APER_GetTrigger() ???w????		*
*		?h?c???????f?o?C?X???????n?????????????A?R?[???????????B		*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		int					id;											*
*		trigger_handler_t	handler;									*
*																		*
*		<id> ???A?T?^?[???y???t?F?????h?c								*
*		<handler> ???A?g???K?n???h??									*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		????															*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		GetTrigger	influence	?g???K?n???h?????e?[?u??				*
*																		*
*																		*
************************************************************************/
void	PER_SetTriggerHandler( int	id, trigger_handler_t	handler ){
	GetTrigger[id] = handler;
}

/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		#include	"per_x.h"											*
*																		*
*		handler = PER_GetTriggerHandler( id );							*
*																		*
*		?w?????h?c???????y???t?F?????p???g???K?n???h???????????B		*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		int		id;														*
*																		*
*		?T?^?[???y???t?F?????h?c										*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_handler_t	handler;									*
*																		*
*		?g???K?n???h??													*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		GetTrigger	reference	?g???K?n???h?????e?[?u??				*
*																		*
*																		*
************************************************************************/
trigger_handler_t	PER_GetTriggerHandler( int	id ){
	return	GetTrigger[id];
}

/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		trigger = GetTriggerDigital( &device );							*
*																		*
*		?f?W?^???f?o?C?X?????g???K?????????????B						*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		const SysDevice	*device;										*
*																		*
*		?f?o?C?X????													*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	trigger;											*
*																		*
*		?g???K???????????????B											*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
static trigger_t	GetTriggerDigital( const SysDevice	*device ){
	const SysDevDigital	*this = ( const SysDevDigital * )device;
	
	trigger_t	data_l = ( trigger_t )( ~this->data[1] ) & 0x00ff;
	trigger_t	data_h = ( trigger_t )( ~this->data[0] ) & 0x00ff;
	
	return	( trigger_t )(( data_h << 8 ) | data_l );
}
/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		trigger = GetTriggerAnalog( &device );							*
*																		*
*		?A?i???O?f?o?C?X?????g???K?????????????B						*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		const SysDevice	*device;										*
*																		*
*		?f?o?C?X????													*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	trigger;											*
*																		*
*		?g???K???????????????B											*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
static trigger_t	GetTriggerAnalog( const SysDevice	*device ){
	const SysDevAnalog	*this = ( const SysDevAnalog * )device;
	
	trigger_t	data_l = ( trigger_t )( ~this->data[1] ) & 0x00ff;
	trigger_t	data_h = ( trigger_t )( ~this->data[0] ) & 0x00ff;
	
	return	( trigger_t )(( data_h << 8 ) | data_l );
}
/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		trigger = GetTriggerPointer( &device );							*
*																		*
*		?|?C???e?B???O?f?o?C?X?????g???K?????????????B					*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		const SysDevice	*device;										*
*																		*
*		?f?o?C?X????													*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	trigger;											*
*																		*
*		?g???K???????????????B											*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
static trigger_t	GetTriggerPointer( const SysDevice	*device ){
	const SysDevPointer	*this = ( const SysDevPointer * )device;
	
	trigger_t	data_h = ( trigger_t )( this->status & PT_TRIGGER );
	
	return	( trigger_t )( data_h << 8 );
}
/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		trigger = GetTriggerKeyboard( &device );						*
*																		*
*		?L?[?{?[?h?f?o?C?X?????g???K?????????????B						*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		const SysDevice	*device;										*
*																		*
*		?f?o?C?X????													*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	trigger;											*
*																		*
*		?g???K???????????????B											*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
static trigger_t	GetTriggerKeyboard( const SysDevice	*device ){
	const SysDevKeyboard	*this = ( const SysDevKeyboard * )device;
	
	trigger_t	data_l = ( trigger_t )( ~this->data[1] ) & 0x00ff;
	trigger_t	data_h = ( trigger_t )( ~this->data[0] ) & 0x00ff;
	
	return	( trigger_t )(( data_h << 8 ) | data_l );
}
/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		trigger = GetTriggerMD3B( &device );							*
*																		*
*		???K?h???C?u?p?R?{?^???p?b?h?????g???K?????????????B			*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		const SysDevice	*device;										*
*																		*
*		?f?o?C?X????													*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	trigger;											*
*																		*
*		?g???K???????????????B											*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
static trigger_t	GetTriggerMD3B( const SysDevice	*device ){
	const struct DevMD3B	*this = ( const struct DevMD3B * )device;
	
	trigger_t	data_h = ( trigger_t )( ~this->data[0] ) & 0x00ff;
	
	return	( trigger_t )( data_h << 8 );
}
/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		trigger = GetTriggerMD6B( &device );							*
*																		*
*		???K?h???C?u?p?U?{?^???p?b?h?????g???K?????????????B			*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		const SysDevice	*device;										*
*																		*
*		?f?o?C?X????													*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	trigger;											*
*																		*
*		?g???K???????????????B											*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
static trigger_t	GetTriggerMD6B( const SysDevice	*device ){
	const struct DevMD6B	*this = ( const struct DevMD6B * )device;
	
	trigger_t	data_l = ( trigger_t )( ~this->data[1] ) & 0x00ff;
	trigger_t	data_h = ( trigger_t )( ~this->data[0] ) & 0x00ff;
	
	return	( trigger_t )(( data_h << 8 ) | data_l );
}
/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		trigger = GetTriggerMDMouse( &device );							*
*																		*
*		???K?h???C?u?p?}?E?X?i???????A?T?^?[???p???V???g???}?E?X???j	*
*		?????g???K?????????????B										*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		const SysDevice	*device;										*
*																		*
*		?f?o?C?X????													*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	trigger;											*
*																		*
*		?g???K???????????????B											*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
static trigger_t	GetTriggerMDMouse( const SysDevice	*device ){
	const struct DevMDMouse	*this = ( const struct DevMDMouse * )device;
	
	trigger_t	data_h = ( trigger_t )( this->status & PT_TRIGGER );
	
	return	( trigger_t )( data_h << 8 );
}
/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		trigger = GetTriggerUnknown( &device );							*
*																		*
*		?s?????f?o?C?X?????g???K?????????????B							*
*																		*
*		???? 0 ???????????B												*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		const SysDevice	*device;										*
*																		*
*		?f?o?C?X????													*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	trigger;											*
*																		*
*		???? 0 ???????????B												*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
static trigger_t	GetTriggerUnknown( const SysDevice	*device ){
	return	0;
}
/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		#include	"per_x.h"											*
*																		*
*		trigger = PER_GetTrigger( device );								*
*																		*
*		?f?o?C?X???????????????g???K?????????????B						*
*																		*
*		PER_SetTriggerHandler() ?????????o?^???????????h?c???????f?o	*
*		?C?X?????g???K???????????o???????A?????? PER_SetTriggerHandler()*
*		?????????o?^???????????????i?n???h???j???p???????B??????????	*
*		???????????????????A?f?t?H???g???p?????????????????i?n???h???j	*
*		???p???????B?????????A?\???????????????????y???t?F?????????L	*
*		???????????????????A???????O???????y???t?F?????????g???K????	*
*		?????????????????APER_SetTriggerHandler() ???g?p?????????????B	*
*																		*
*		?f?t?H???g???????????????????y???t?F????						*
*		?f?W?^???f?o?C?X												*
*			?T?^?[???y???t?F?????h?c?????? 0x02 - 0x0f ??????????		*
*		?A?i???O?f?o?C?X												*
*			?T?^?[???y???t?F?????h?c?????? 0x12 - 0x1f ??????????		*
*		?|?C???e?B???O?f?o?C?X											*
*			?T?^?[???y???t?F?????h?c?????? 0x22 - 0x2f ??????????		*
*		?L?[?{?[?h?f?o?C?X												*
*			?T?^?[???y???t?F?????h?c?????? 0x33 - 0x3f ??????????		*
*		???K?h???C?u?p?R?a?p?b?h										*
*			?T?^?[???y???t?F?????h?c?????? 0xe1 ??????????				*
*		???K?h???C?u?p?U?a?p?b?h										*
*			?T?^?[???y???t?F?????h?c?????? 0xe2 ??????????				*
*		???K?h???C?u?p?}?E?X											*
*			?T?^?[???y???t?F?????h?c?????? 0xe3 ??????????				*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		const SysDevice	*device;										*
*																		*
*		?f?o?C?X????													*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	trigger;											*
*																		*
*		?g???K???????????????B											*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
trigger_t	PER_GetTrigger( const SysDevice	*this ){
	trigger_t	trigger = 0;
	
	if( this != NULL ){
		int					id = PER_GetID( this );
		trigger_handler_t	handler = PER_GetTriggerHandler( id );
		
		if( handler != NULL )
			trigger = handler( this );
	}
	
	return	trigger;
}
/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		#include	"per_x.h"											*
*																		*
*		edge = PER_GetEdge( t1, t2 );									*
*																		*
*		?g???K???G?b?W?????????????B									*
*																		*
*		?G?b?W???????? <t1> ?? <t2> ???Q?????^?C?~???O??????????????	*
*		?????g???K???????????????????????B								*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		trigger_t	t1;													*
*		trigger_t	t2;													*
*																		*
*		<t1> ?? <t2> ???g???K?????B										*
*		<t1> ?? <t2> ???????I???????????????????B						*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	edge;												*
*																		*
*		?g???K???G?b?W???????????????B									*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
trigger_t	PER_GetEdge( trigger_t	t1, trigger_t	t2 ){
	return	( trigger_t )( t1 ^ t2 );
}
/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		#include	"per_x.h"											*
*																		*
*		edge = PER_GetPressEdge( prev, current );						*
*																		*
*		?g???K???v???X?G?b?W?i?????G?b?W?j?????????????B				*
*																		*
*		?v???X?G?b?W???????? <prev> ?? <current> ???Q?????^?C?~???O		*
*		???????????????[?X?????????v???X???????????????g???K????????	*
*		???????????????B												*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		trigger_t	prev;												*
*		trigger_t	current;											*
*																		*
*		<prev> ?? <current> ???????g???K?????B							*
*		?????I???i <prev> ?? <current> ?j?????????W?????????????????B	*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	edge;												*
*																		*
*		?g???K???v???X?G?b?W???????????????B							*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
trigger_t	PER_GetPressEdge( trigger_t	prev, trigger_t	current ){
	trigger_t	edge = PER_GetEdge( prev, current );
	
	return	( trigger_t )( current & edge );
}

/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		#include	"per_x.h"											*
*																		*
*		edge = PER_GetReleaseEdge( prev, current );						*
*																		*
*		?g???K???????[?X?G?b?W?i?????G?b?W?j?????????????B				*
*																		*
*		?????[?X?G?b?W???????? <prev> ?? <current> ???Q?????^?C?~??		*
*		?O???????????v???X?????????????[?X???????????????g???K??????	*
*		?????????????????B												*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		trigger_t	prev;												*
*		trigger_t	current;											*
*																		*
*		<prev> ?? <current> ???????g???K?????B							*
*		?????I???i <prev> ?? <current> ?j?????????W?????????????????B	*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		trigger_t	edge;												*
*																		*
*		?g???K???????[?X?G?b?W???????????????B							*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
trigger_t	PER_GetReleaseEdge( trigger_t	prev, trigger_t	current ){
	trigger_t	edge = PER_GetEdge( prev, current );
	
	return	( trigger_t )( ~current & edge );
}

#define	ANALOG_ILLEGAL	0xff
#define	ANALOG_ORIGIN	0x7f

/*@*/
/************************************************************************
*																		*
*	?ysynopsis?z														*
*																		*
*		#include	"per_x.h"											*
*																		*
*		PER_GetAnalogXYZ( analog, &x, &y, &z );							*
*																		*
*		?A?i???O?f?o?C?X?????w?x?y???????`?^?c?R???o?[?^???o???l????	*
*		?????B															*
*																		*
*																		*
*	?yparameters?z														*
*																		*
*		const SysDevAnalog	*analog;									*
*		int		*x;														*
*		int		*y;														*
*		int		*z;														*
*																		*
*		<analog> ???A?i???O?f?o?C?X?????B								*
*		<x> <y> <z> ???????????w?x?y???????`?^?c?R???o?[?^???o???l?B	*
*																		*
*		<x> <y> <z> ?? NULL ???n?????????????????????????????B			*
*																		*
*		<x> ?????i?E?j-127 ?` +127?i???j?????????????B					*
*		<y> ?????i???j-127 ?` +127?i???j?????????????B					*
*		<z> ?????i???j-127 ?` +127?i???j?????????????B					*
*																		*
*																		*
*	?yreturn value?z													*
*																		*
*		????															*
*																		*
*																		*
*	?yinfluence/reference objects?z										*
*																		*
*		????															*
*																		*
*																		*
************************************************************************/
void	PER_GetAnalogXYZ( const SysDevAnalog	*this, int	*x, int	*y, int	*z ){
	int		ax = 0;
	int		ay = 0;
	int		az = 0;
	
	if( this->ax != ANALOG_ILLEGAL )
		ax = ( int )this->ax - ANALOG_ORIGIN;
	if( this->ay != ANALOG_ILLEGAL )
		ay = ( int )this->ay - ANALOG_ORIGIN;
	if( this->az != ANALOG_ILLEGAL )
		az = ( int )this->az - ANALOG_ORIGIN;
	
	if( x != NULL )
		*x = ax;
	if( y != NULL )
		*y = ay;
	if( z != NULL )
		*z = az;
}


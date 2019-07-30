#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
typedef int DataType;
typedef struct array
{
	DataType	*Data;
	int		size, max_size;
	void (*Constructor)( struct array * );                /* 构造函数 */
	void (*Input)( DataType, struct array * );              /* 输入数据 */
	int (*get_array_size)( struct array * );             /* 获取arr的大小 */
	int (*return_index_value)( struct array *, int );    /* 返回下标为index的值 */
	void (*print)( struct array * );                        /* 打印结果 */
	void (*Destructor)( struct array * );                   /* 析构函数 */
} Array;

void Init( Array *this );


void _print( struct array *this );


void _constructor( Array *this );


void _denstructor( Array *this );


void _input( DataType data, Array *this );


int _get_size( Array *this );


int _return_index_value( Array *this, int index );


void Init( Array *this )
{
	this->Input			= _input;
	this->print			= _print;
    this->get_array_size		= _get_size;
    this->return_index_value	= _return_index_value;
	this->Constructor		= _constructor;
	this->Destructor		= _denstructor;
	this->Constructor( this );
}


void _constructor( Array *this )
{
	this->size	= 0;
	this->max_size	= 10;
	this->Data	= (DataType *) malloc( this->max_size * sizeof(DataType) );
	memset( this->Data, 0, 10 );
}


void _input( DataType data, Array *this )
{
	int		i;
	DataType	*ptr;

	if ( this->size >= this->max_size )
	{
		this->max_size	+= 10;
		ptr		= (DataType *) malloc( this->max_size * sizeof(DataType) );
		for ( i = 0; i < this->size; i++ )
			ptr[i] = this->Data[i];
		free( this->Data );
		this->Data = ptr;
	}
	this->Data[this->size]	= data;
	this->size		+= 1;
}


void _print( struct array *this )
{
	assert( this != NULL );
	struct array	*ptr	= this;
	int		i	= 0;
	for ( i = 0; i < ptr->size; i++ )
		printf( "data is %d\n", ptr->Data[i] );

	return;
}


int _get_size( Array *this )
{
	 assert( this != NULL );
	return(this->size + 1);
}


int _return_index_value( Array *this, int index )
{
	 assert( this != NULL );
	return(this->Data[index]);
}


void _denstructor( Array *this )
{
	int i = 0;
	  assert( this != NULL );
	for ( i = 0; i < this->max_size; i++ )
		this->Data[i] = 0;
	free( this->Data );
}


int main()
{
	Array a;

	Init( &a ); /* 使用对象前必须初始化，间接调用构造函数 */
	/* a.Data[]={1,2,3,4,5}; */
	a.Input( 1, &a );
	a.Input( 2, &a );
	a.Input( 3, &a );
	a.Input( 4, &a );
	a.Input( '5', &a );
	a.print( &a );
//printf( "the array size is :%d\n", a.get_array_size( &a ) );
//printf( "the index value in array is:%d\n", a.return_index_value( &a, 3 ) );
	a.Destructor( &a ); /* 使用对象后必须显式调用析构函数 */

	return(0);
}

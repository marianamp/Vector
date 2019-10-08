#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list> // std::initializer_list

namespace sc {
 	template < typename T> 
 	class vector { 
 		public:
            class MyIterator{
                private:
                    T *current;
                public:
                    // Below we have the iterator_traits common interface
			        /// Difference type used to calculated distance between iterators.
			        typedef std::ptrdiff_t difference_type;
			        typedef T value_type; //!< Value type the iterator points to.
			        typedef T* pointer; //!< Pointer to the value type.
			        typedef T& reference; //!< Reference to the value type.
			        typedef std::bidirectional_iterator_tag iterator_category; //!< Iterator category.

			        MyIterator( ):
			        	current{ nullptr}
			        {/* empty */}  

			        MyIterator& operator=( const MyIterator& ) = default;

			        MyIterator( const MyIterator& ) = default;
                       
			        reference operator* ( ) const
			        {
			        	return *current;
			        }

			        pointer operator->( void ) const 
			        { 
			        	assert( current != nullptr ); 
			        	return current; 
			        }

			        MyIterator& operator++ ( )
			        {
			        	current++;//era ++current
			        	return *this;
			        }

			        MyIterator operator++ ( int )
			        {
			        	MyIterator temp( current );
			        	current++;
			        	return temp;
			        } 

			        MyIterator& operator-- ( )
			        {
			        	current--;//era --current
			        	return *this;
			        }

			        MyIterator operator-- ( int )
			        {
			        	MyIterator temp( current );
			        	current--;
			        	return temp;
			        }

			        friend MyIterator operator+( difference_type offset )
			        {			        	
			        	return MyIterator(current + offset);
			        }

			        friend MyIterator operator+( MyIterator& i )
			        {
			        	return MyIterator(current + i);
			        }

			        friend MyIterator operator-( difference_type offset )
			        {
			        	return MyIterator(current - offset);
			        }

			        friend MyIterator operator-( MyIterator& i )
			        {
			        	return MyIterator(current - i);
			        }
			        			        
			        bool operator== ( const MyIterator& i) const
			        {
			        	return *this == i.current;
			        }

			        bool operator!= ( const MyIterator& i) const
			        {
			        	return !(*this == i.current);
			        }

            };

        private: 
	       	size_type m_size; //!< Current list size (or index past-last valid element). 
	       	size_type m_capacity; //!< List’s storage capacity.
	       	//std::unique_ptr<T[]> m_storage; //!< Data storage area for the dynamic array. 
	       	T *m_storage;//!< Data storage area for the dynamic array.   

 		public: 
	 		using size_type = unsigned long; //!< The size type. 
			using value_type = T; //!< The value type.
	 		using pointer = value_type*; //!< Pointer to a value stored in the container. 
	 		using reference = value_type&; //!< Reference to a value stored in the container. 
	  		using const_reference = const value_type&; //!< Const reference to a value stored in the container 
	  		using iterator = MyIterator< T >; // See Code 3 
	  		using const_iterator = MyIterator< const T >; // See Code 3 
  
	    	//=================================================== [I] SPECIAL MEMBERS=================================================================
	    	vector( )
	    	{
	    		this->m_size =  0;
				this->m_capacity = 0;
			 	this->m_storage = new T[ nullptr ];
			} 
	    	
			explicit vector( size_type count )
			{
				this->m_size = 0;
				this->m_capacity = count;
				this->m_storage = new T[ this->m_capacity ]; 
			
			  	for(size_type i{0};i<this->m_size;i++){
			    	m_storage[i] = T();//construtor default, dá certo pra todo tipo de dado
			  	}
			}
			 	
	    	virtual ~vector( void )
	    	{
	    		delete [] m_storage;
	    	}

			template < typename InputItr > 
	      	vector( InputItr first, InputItr last)
	      	{
	      		this->m_size = last - first;
				this->m_capacity = this->m_size ;
				this->m_storage = new T[ this->m_capacity ];
	      	
	      		for(size_type i{0};i<this->m_size;i++){
					m_storage[i] = *first++;
				}
	      	}

	     	vector( const vector & other)     		
	     	{
	     		this->m_size = other.size;
  				this->m_capacity = this->m_size;
  				this->m_storage = new T[ this->m_capacity ];
	     	
	     		for(size_type i{0};i<this->m_size;i++){
					m_storage[i] = other.m_storage[i];
				}
	     	}
	    
	     	vector(std::initializer_list<T> ilist)
	     	{
	     		this->m_size = ilist.size();
  				this->m_capacity = this->m_size ;
  				this->m_storage =  new T[ this->m_capacity ];
	     	
	     		size_type count{0};
  				for (const T& elem : ilist){
    				m_storage[count++] = elem; 
  				}
	     	}
	     	
	     	vector( vector && );

	     	vector& operator=( const vector& other)
	      	{
	      		if( *this != &other ) {
				  	delete [] m_storage;    
				  	this->m_size = other.size;
				  	this->m_capacity = this->m_size;
				  	this->m_storage = new T[this->m_capacity];
				  	for(size_type i{0};i<this->m_size; i++){
				    	m_storage[i] = other.m_storage[i];
				  	}
				  }
				return *this;
	      	}

	      	vector& operator=( std::initializer_list<T> ilist )
	      	{
	      		if( *this != ilist ) {
  					delete [] m_storage;    
  					this->m_size = ilist.size();
  					this->m_capacity = this->m_size;
  					this->m_storage = new T[this->m_capacity];
    				int count = 0;
    				for (const T& elem : ilist){
      					m_storage[count++] = elem; 
    				}
 				}
				return *this;
	      	}

	      	vector& operator=( vector && ); 
	      		      
	     	//================================================= [II] ITERATORS=====================================================================
	      	iterator begin( void )
	      	{
	      		return MyIterator(&m_storage[0]);
	      	} 
	      	iterator end( void )
	      	{
	      		return MyIterator(&m_storage[this->m_size]);
	      	} 
	      	const_iterator cbegin( void ) const
	      	{
	      		return MyIterator(&m_storage[0]);
	      	}
	       	const_iterator cend( void ) const
	       	{
	       		return MyIterator(&m_storage[this->m_size]);
	       	}
			
	       	//========================================================== [III] CAPACITY ============================================================s
	       	size_type size( void ) const
	       	{
	       		return this->m_size;
	       	}
	       	size_type capacity( void ) const
	       	{
	       		return this->m_capacity;
	       	} 
	       	bool empty( void ) const
	       	{
	       		return this->m_size == 0;
	       	}
	       	
		    //============================================================== [IV] MODIFIERS=========================================================  
		    void clear( void )
		    {
		    	this->m_size = 0;
		    } 
		    void push_front( const_reference value)
		    {
		    	if (this->m_size == this->m_capacity){
      				if (this->m_capacity == 0){
        				reserve(1);
      				}
	      			else{
	          			reserve(2 * this->m_capacity);
	      			}
				 }
				this->m_size++;
				for( size_type i{this->m_size-1};i>0;i--){
					m_storage[i] = m_storage[i-1];
				}
				m_storage[0] = value; 
		    }
		    void push_back( const_reference value)
		    {
		    	if (this->m_size == this->m_capacity){
			      if (this->m_capacity == 0){
			        reserve(1);
			      }
			      else{
			          reserve(2 * this->m_capacity);
			      }
			  	}
			    this->m_size++;
			    m_storage[this->m_size] = value;
		    }
		    void pop_back( void )
		    {
		    	this->m_size--;
		    }
		    void pop_front( void )
		    {
  				for( size_type i{0} ; i < this->m_size ; ++i ){
    				m_storage[i] = m_storage[i+1];
  				}
  				this->m_size--;
		    } 
		    iterator insert( iterator pos, const_reference value)
		    {
		    	if (this->m_size == this->m_capacity){
			      if (this->m_capacity == 0){
			        reserve(1);
			      }
			      else{
			          reserve(2 * this->m_capacity);
			      }
			  	}
		    	this->m_size++;
		    	for(size_type i{this->m_size-1};i>=pos;i--){
		    		m_storage[i] = m_storage[i-1];
		    	}
		    	m_storage[pos-1] = value;
		    	return iterator(pos-1);
		    } 
		    /*
		    template < typename InputItr > 
		    iterator insert( iterator pos, InputItr first, InputItr last)
		    {

		    }
		    iterator insert( iterator pos, const std::initializer_list< value_type >& ilist)
		    {
		    	
		    }
		    */
		    void reserve( size_type new_cap)
		    {
		    	if (new_cap > this->m_capacity){
				    T * temp = new T[ new_cap ];
				    for(int i=0;i<this->m_size; i++){
				      temp[i] = m_storage[i];
				    }
				    delete[] m_storage;
				    m_storage = temp;
				    m_capacity = new_cap;
			  	}
		    } 
		    /*
		    void shrink_to_fit( void )
		    {

		    }
		    */
		    void assign( size_type count, const_reference value)
		    {
		    	for(size_type i{0};i<count;i++){
		    		m_storage[i] = value;
		    	}
		    }
		    void assign( const std::initializer_list<T>& ilist)
		    {
		    	size_type i{0};
  				for (const T& elem : ilist){
    				m_storage[i++] = elem; 
  				}
		    } 
		    template < typename InputItr > 
		    void assign( InputItr first, InputItr last)
		    {
		    	size_type i{0};
		    	while(first != last){
					m_storage[i++] = *first++;
		    	}
		    } 
		    /*   
		    iterator erase( iterator, iterator )
		    {

		    }
		    iterator erase( iterator )
		    {

		    }
		    */   
		    //============================================================ [V] ELEMENT ACCESS=========================================================
		    const_reference back( void ) const
		    {
		    	return m_storage[this->m_size - 1];
		    }
		    reference back( void )
		    {
		    	return m_storage[this->m_size - 1];
		    } 
		    const_reference front( void ) const
		    {
		    	return m_storage[0];
		    }
		    reference front( void )
		    {
		    	return m_storage[0];
		    }
		    const_reference operator[]( size_type pos) const
		    {
		    	return m_storage[pos];
		    } 
		    reference operator[]( size_type pos)
		    {
		    	return m_storage[pos];
		    }
		    const_reference at( size_type pos) const
		    {
		    	if ( pos >= this->m_size ){
    				throw std::out_of_range("Accessed position is out of range!");
  				}
  				return m_storage[pos];
		    } 
		    reference at( size_type pos)
		    {
		    	if ( pos >= this->m_size ){
    				throw std::out_of_range("Accessed position is out of range!");
  				}
  				return m_storage[pos];
		    }
		    pointer data( void )
		    {
		    	return m_storage;
		    } 
		    const_reference data( void ) const
		    {
		    	return m_storage;
		    }    
		    //============================================== [VII] FRIEND FUNCTIONS===================================================================
		    /*friend std::ostream& operator<<( std::ostream& os, const vector<T>& v)
		    {

		    }*/
		    friend void swap( vector<T>& a, vector<T>& b)
		    {
		 		T temp = a;
				a = b;
				b = temp;
		    } 
		    //============================================== [VII] NON MEMBER FUNCTIONS===============================================================
		    bool operator==( const vector& rhs )
			{
				if(this->m_size == rhs.m_size){
					for(size_type i{0};i<this->m_size;i++){
						if(!(m_storage[i] == rhs.m_storage[i])){
							return false;
						}
					}
					return true;
				}
				else{
					return false;
				}
			}

			bool operator!=( const vector& rhs )
			{
				if(this->m_size == rhs.m_size){
					for(size_type i{0};i<this->m_size;i++){
						if(m_storage[i] == rhs.m_storage[i]){
							return false;
						}
					}
					return true;
				}
				else{
					return false;
				}
			}
	};
}	
#endif


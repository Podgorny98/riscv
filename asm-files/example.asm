    #Use after free modeling

    #a5 - pointer to heap
    #t1 - tag
    addi a5, zero, 200
	addi t1, t1, 1
	

    #tagging pointer
	sptg t1, 0(a5)

    #1 byte alloc/tagging
    stg a5, 0(t1)

    addi t2, zero, 13

    #before writing data check tags(compiler work)
    cmptg a5, 0(t1)

    #store data
    sw t2, 0(a5)
    #load data
    lw t3, 0(a5)
    
    #free memory(change tag)
    addi t3, t3, 4
    stg a5, 0(t3)

    cmptg a5, 0(t1)
    lw t3, 0(a5)
    

project(examples)

#+++++++++++++++++++++++++++++++
# Hydra phase-space generation |
#+++++++++++++++++++++++++++++++
                                         
#+++++++++++++++++++++++++
# CUDA TARGETS           |
#+++++++++++++++++++++++++
if(BUILD_CUDA_TARGETS)
         #+++++++++++++++++++++++++++++++++
         cuda_add_executable( phsp_basic_cuda EXCLUDE_FROM_ALL  phsp_basic.cu    
            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
            )
         target_link_libraries(phsp_basic_cuda  ${ROOT_LIBRARIES} )
         
         #+++++++++++++++++++++++++++++++++
         cuda_add_executable( phsp_chain_cuda EXCLUDE_FROM_ALL phsp_chain.cu    
            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
            )
         target_link_libraries(phsp_chain_cuda ${ROOT_LIBRARIES}  )
        
         #+++++++++++++++++++++++++++++++++
         cuda_add_executable( phsp_averaging_functor_cuda EXCLUDE_FROM_ALL phsp_averaging_functor.cu    
            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
            )
         target_link_libraries(phsp_averaging_functor_cuda ${ROOT_LIBRARIES}  )    
         
         #+++++++++++++++++++++++++++++++++
         cuda_add_executable( phsp_evaluating_functor_cuda EXCLUDE_FROM_ALL phsp_evaluating_functor.cu    
            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
            )
         target_link_libraries(phsp_evaluating_functor_cuda ${ROOT_LIBRARIES}  )    
         
                        
endif(BUILD_CUDA_TARGETS)

#+++++++++++++++++++++++++
# TBB TARGETS           |
#+++++++++++++++++++++++++
if(BUILD_TBB_TARGETS)

    #+++++++++++++++++++++++++++++++
    add_executable( phsp_basic_tbb EXCLUDE_FROM_ALL
     phsp_basic.cpp
    )
    
    set_target_properties( phsp_basic_tbb PROPERTIES 
    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
    
    target_link_libraries( phsp_basic_tbb   ${ROOT_LIBRARIES} tbb )
   
    #+++++++++++++++++++++++++++++++
    add_executable( phsp_chain_tbb EXCLUDE_FROM_ALL
    phsp_chain.cpp
    )
    
    set_target_properties(phsp_chain_tbb PROPERTIES 
    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
    
    target_link_libraries(phsp_chain_tbb   ${ROOT_LIBRARIES} tbb )
   
    #+++++++++++++++++++++++++++++++
    add_executable( phsp_averaging_functor_tbb EXCLUDE_FROM_ALL
    phsp_averaging_functor.cpp
    )
    
    set_target_properties(phsp_averaging_functor_tbb PROPERTIES 
    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
    
    target_link_libraries(phsp_averaging_functor_tbb   ${ROOT_LIBRARIES} tbb )
    
    #+++++++++++++++++++++++++++++++
    add_executable( phsp_evaluating_functor_tbb EXCLUDE_FROM_ALL
    phsp_evaluating_functor.cpp
    )
    
    set_target_properties(phsp_evaluating_functor_tbb PROPERTIES 
    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
    
    target_link_libraries(phsp_evaluating_functor_tbb   ${ROOT_LIBRARIES} tbb )
    
    
        
endif(BUILD_TBB_TARGETS)


#+++++++++++++++++++++++++
# OMP TARGETS            |
#+++++++++++++++++++++++++
IF(OPENMP_FOUND)

    #+++++++++++++++++++++++++++++++
    add_executable(phsp_basic_omp EXCLUDE_FROM_ALL
    phsp_basic.cpp
    )
    
    set_target_properties( phsp_basic_omp PROPERTIES 
    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
    
    target_link_libraries( phsp_basic_omp
    ${ROOT_LIBRARIES}
    rt
    )

    #+++++++++++++++++++++++++++++++
    add_executable( phsp_chain_omp EXCLUDE_FROM_ALL
    phsp_chain.cpp
    )
    
    set_target_properties( phsp_chain_omp PROPERTIES 
    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
    
    target_link_libraries( phsp_chain_omp
    ${ROOT_LIBRARIES}
    rt
    )
    #+++++++++++++++++++++++++++++++
    add_executable( phsp_averaging_functor_omp EXCLUDE_FROM_ALL
    phsp_averaging_functor.cpp
    )
    
    set_target_properties( phsp_averaging_functor_omp PROPERTIES 
    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
    
    target_link_libraries( phsp_averaging_functor_omp
    ${ROOT_LIBRARIES}
    rt
    )

    #++++++++++++++++++++++++++++
    add_executable( phsp_evaluating_functor_omp EXCLUDE_FROM_ALL
    phsp_evaluating_functor.cpp
    )
    
    set_target_properties( phsp_evaluating_functor_omp PROPERTIES 
    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
    
    target_link_libraries( phsp_evaluating_functor_omp
    ${ROOT_LIBRARIES}
    rt
    )
endif(OPENMP_FOUND)


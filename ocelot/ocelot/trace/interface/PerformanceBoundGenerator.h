/*! \file PerformanceBoundGenerator.h

	\author Andrew Kerr <arkerr@gatech.edu>

	\brief computes operations, flops, and memory bandwidth per basic block
*/

#ifndef TRACE_PERFORMANCEBOUNDGENERATOR_H_INCLUDED
#define TRACE_PERFORMANCEBOUNDGENERATOR_H_INCLUDED

// Ocelot includes
#include <ocelot/trace/interface/TraceGenerator.h>
#include <ocelot/api/interface/OcelotConfiguration.h>
#include <fstream>

namespace trace {

	/*!
		Base class for generating traces
	*/
	class PerformanceBoundGenerator: public TraceGenerator {	
	public:
	
		class Counter {
		public:
			Counter();
			
			Counter & operator += (const Counter &c) {
				memoryDemand += c.memoryDemand;
				instructions += c.instructions;
				flops += c.flops;
				sharedBytes += c.sharedBytes;
				bankConflicts += c.bankConflicts;
				return *this;
			}
			
		public:
		
			//! \brief bytes transferred to or from global memory [including texture samples]
			size_t memoryDemand;
			
			//! \brief dynamic instructions
			size_t instructions;
			
			//! \brief floating-point operations [subset of dynamic instructions]
			size_t flops;
			
			//! \brief counts number of bytes loaded or stored to shared memory
			size_t sharedBytes;
			
			/*! 
				\brief incremented every time a thread conflicts with the address bank of an earlier
					thread in the half-warp - efficiency of shared memory access
			*/
			size_t bankConflicts;
		};
		
		//! \brief maps basic block label to operation counters
		typedef std::map< std::string, Counter > OperationCounterMap;
	
	public:
		PerformanceBoundGenerator();
		virtual ~PerformanceBoundGenerator();

		/*! \brief called when a traced kernel is launched to retrieve some 
				parameters from the kernel
		*/
		virtual void initialize(const executive::ExecutableKernel& kernel);

		/*! \brief Called whenever an event takes place.

			Note, the const reference 'event' is only valid until event() 
			returns
		*/
		virtual void event(const TraceEvent & event);
		
		/*! \brief Called when a kernel is finished. There will be no more 
				events for this kernel.
		*/
		virtual void finish();
		
	protected:
	
		//! \brief visits each basic block and initializes a counter for each block
		void analyzeKernel(const executive::EmulatedKernel &kernel);
		
		//! \brief computes the number of bytes of effective demand from an event given a coalescing protocol
		static size_t computeMemoryDemand(const trace::TraceEvent &event, 
			api::OcelotConfiguration::TraceGeneration::PerformanceBound::CoalescingProtocol protocol);
		
		//! \brief determines if instruction is a significant floating-point operation
		static int isFlop(const ir::PTXInstruction &instr);

		//! \brief tests
		static bool isGlobalMemoryOp(const ir::PTXInstruction &instr);
		
		//! \brief computes bytes loaded or stored to shared memory and number of conflicts
		static size_t computeSharedDemand(const trace::TraceEvent &event, int * conflicts);
	
	public:
	
		//! \brief specifies the active memory coalescing protocol to employ
		api::OcelotConfiguration::TraceGeneration::PerformanceBound::CoalescingProtocol protocol;
		
		//! \brief kernel
		const executive::EmulatedKernel * kernel;

		/*! \brief Counter for creating unique file names. */
		static unsigned int _counter;
		
		/*!	\brief Entry for the current kernel	*/
		KernelEntry _entry;
		
	
		//! \brief maps basic blocks onto performance counters
		OperationCounterMap counterMap;
		
		//! maps the PC of the last instruction of each block to the block's label
		std::map< int, std::string > PCsToBlocks;
	};
}

std::ostream & operator <<(std::ostream &out, const trace::PerformanceBoundGenerator::Counter &counter);

#endif

#ifndef DRIVER_HH
#define DRIVER_HH

#include "common.hh"

/** The xigen namespace is used to encapsulate the three parser classes
	* xigen::Parser, xigen::Scanner and xigen::Driver */
namespace xigen {

	// forward declaration
	class ParserContext;

	/** The Driver class brings together all components. It creates an instance of
	 * the Parser and Scanner classes and connects them. Then the input stream is
	 * fed into the scanner object and the parser gets it's token
	 * sequence. Furthermore the driver object is available in the grammar rules as
	 * a parameter. Therefore the driver class contains a reference to the
	 * structure into which the parsed data is saved. */
	class Driver
	{
		public:
			/// construct a new parser driver context
			Driver(ParserContext& context);

			/// enable debug output in the flex scanner
			bool trace_scanning;

			/// enable debug output in the bison parser
			bool trace_parsing;

			bool trace_ast;

			bool trace_warnings;

			bool no_comments;

			/// stream name (file or input stream) used for error messages.
			std::string streamname;

			/** Invoke the scanner and parser for a stream.
			 * @param in	input stream
			 * @param sname	stream name for error messages
			 * @return		true if successfully parsed
			 */
			bool parse_stream(std::istream& in,
					const std::string& sname = "stream input");

			/** Invoke the scanner and parser on an input string.
			 * @param input	input string
			 * @param sname	stream name for error messages
			 * @return		true if successfully parsed
			 */
			bool parse_string(const std::string& input,
					const std::string& sname = "string stream");

			/** Invoke the scanner and parser on a file. Use parse_stream with a
			 * std::ifstream if detection of file reading errors is required.
			 * @param filename	input file name
			 * @return		true if successfully parsed
			 */
			bool parse_file(const std::string& filename);

			// To demonstrate pure handling of parse errors, instead of
			// simply dumping them on the standard error output, we will pass
			// them to the driver using the following two member functions.

			/** Error handling with associated line number. This can be modified to
			 * output the error e.g. to a dialog box. */
			void report(const class location& l, const std::string& m);

			/** General error handling. This can be modified to output the error
			 * e.g. to a dialog box. */
			void report(const std::string& m);

			class Scanner* getLexer() { return m_lexer; }

			class ParserContext& getContext() { return m_context; }


		private:
			/** Pointer to the current lexer instance, this is used to connect the
			 * parser to the scanner. It is used in the yylex macro. */
			class Scanner* m_lexer;

			/** Reference to the context */
			class ParserContext& m_context;
	};

} // namespace xigen

#endif // DRIVER_H
/* vim: set ts=2 sw=2: */

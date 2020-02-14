///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "facade/FacadeParser.h"
#include "parse/parserCSV.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of IParser interface.
	/// </summary>
	class FacadeParserCSV : public FacadeParser
	{
		// public construction and destruction methods
	public:

		explicit FacadeParserCSV(std::shared_ptr<core::Core> core, particles::ParticleSystem& ps);
		~FacadeParserCSV() = default;

		FacadeParserCSV(const FacadeParserCSV&) = delete;
		FacadeParserCSV(FacadeParserCSV&&) = delete;

		FacadeParserCSV& operator=(const FacadeParserCSV&) = delete;
		FacadeParserCSV& operator=(FacadeParserCSV&&) = delete;

		// public methods
	public:
		void loadFile(std::string filePath) override;

		// private members
	private:
		std::shared_ptr<ivhd::parse::ParserCSV> m_internalParser;

		particles::ParticleSystem& m_ext_particleSystem;
	};
}
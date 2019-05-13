///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "ivhd/IParser.h"
#include "core/ParticleSystem.h"
#include "parse/parserCSV.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of IParser interface.
	/// </summary>
	class FacadeParserCSV : public IParser
	{
		// public construction and destruction methods
	public:

		explicit FacadeParserCSV(core::ParticleSystem& system);
		~FacadeParserCSV() = default;

		FacadeParserCSV(const FacadeParserCSV&) = delete;
		FacadeParserCSV(FacadeParserCSV&&) = delete;

		FacadeParserCSV& operator=(const FacadeParserCSV&) = delete;
		FacadeParserCSV& operator=(FacadeParserCSV&&) = delete;

		// public methods
	public:
		void loadFile(std::string filePath) override;

	private:
		ivhd::parse::ParserCSV m_internalParser;
	};
}
import pyviskit_bindings as bindings
from pyviskit.AbstractCaster import AbstractCaster


class LargeVis(AbstractCaster):
    def __init__(
        self,
        optimizer_type: bindings.OptimizerType,
        parser_type: bindings.ParserType = bindings.ParserType.Csv,
        graph_generator_type: bindings.GraphGeneratorType = bindings.GraphGeneratorType.Random,
        **kwargs
    ):
        super().__init__(
            bindings.CasterType.LargeVis,
            optimizer_type,
            parser_type,
            graph_generator_type,
            **kwargs
        )

    # TODO - maybe it would be better to read dataset and labels in form of dataframes and write it to files ourselves??
    def fit_transform(
        self,
        dataset_file_path,
        labels_file_path,
        graph_file_path,
        output_file_path=None,
    ):
        return super().fit_transform(
            dataset_file_path, labels_file_path, graph_file_path, output_file_path
        )

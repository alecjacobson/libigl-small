py::enum_<igl::PerEdgeNormalsWeightingType>(m, "PerEdgeNormalsWeightingType")
    .value("PER_EDGE_NORMALS_WEIGHTING_TYPE_UNIFORM", igl::PER_EDGE_NORMALS_WEIGHTING_TYPE_UNIFORM)
    .value("PER_EDGE_NORMALS_WEIGHTING_TYPE_AREA", igl::PER_EDGE_NORMALS_WEIGHTING_TYPE_AREA)
    .value("PER_EDGE_NORMALS_WEIGHTING_TYPE_DEFAULT", igl::PER_EDGE_NORMALS_WEIGHTING_TYPE_DEFAULT)
    .value("NUM_PER_EDGE_NORMALS_WEIGHTING_TYPE", igl::NUM_PER_EDGE_NORMALS_WEIGHTING_TYPE)
    .export_values();


m.def("per_edge_normals", []
(
  const Eigen::MatrixXd& V,
  const Eigen::MatrixXi& F,
  const igl::PerEdgeNormalsWeightingType weight,
  const Eigen::MatrixXd& FN,
  Eigen::MatrixXd& N,
  Eigen::MatrixXi& E,
  Eigen::MatrixXi& EMAP
)
{
  return igl::per_edge_normals(V, F, weight, FN, N, E, EMAP);
}, __doc_igl_per_edge_normals,
py::arg("V"), py::arg("F"), py::arg("weight"), py::arg("FN"), py::arg("N"), py::arg("E"), py::arg("EMAP"));

m.def("per_edge_normals", []
(
  const Eigen::MatrixXd& V,
  const Eigen::MatrixXi& F,
  const igl::PerEdgeNormalsWeightingType weight,
  Eigen::MatrixXd& N,
  Eigen::MatrixXi& E,
  Eigen::MatrixXi& EMAP
)
{
  return igl::per_edge_normals(V, F, weight, N, E, EMAP);
}, __doc_igl_per_edge_normals,
py::arg("V"), py::arg("F"), py::arg("weight"), py::arg("N"), py::arg("E"), py::arg("EMAP"));

m.def("per_edge_normals", []
(
  const Eigen::MatrixXd& V,
  const Eigen::MatrixXi& F,
  Eigen::MatrixXd& N,
  Eigen::MatrixXi& E,
  Eigen::MatrixXi& EMAP
)
{
  return igl::per_edge_normals(V, F, N, E, EMAP);
}, __doc_igl_per_edge_normals,
py::arg("V"), py::arg("F"), py::arg("N"), py::arg("E"), py::arg("EMAP"));


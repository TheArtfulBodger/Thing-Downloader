import * as React from 'react';
import QueryString from 'query-string';

import JobsPage from '../../components/JobsPage';

const IndexPage = (props) => {
  let page = parseInt(QueryString.parse(props.location.search).page);
  if (page === null) {
    page = 1;
  }
  return (
    <JobsPage t="failed" page={page}>Failed Jobs</JobsPage>
  );
};

export default IndexPage;

export const Head = () => <title>Failed Jobs</title>;

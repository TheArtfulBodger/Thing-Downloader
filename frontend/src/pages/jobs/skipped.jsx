import * as React from 'react';
import QueryString from 'query-string';

import JobsPage from '../../components/JobsPage';

const IndexPage = (props) => {
  let page = parseInt(QueryString.parse(props.location.search).page);
  if (page === null) {
    page = 1;
  }
  return (
    <JobsPage t="skipped" page={page}>Skipped Jobs</JobsPage>
  );
};

export default IndexPage;

export const Head = () => <title>Skipped Jobs</title>;

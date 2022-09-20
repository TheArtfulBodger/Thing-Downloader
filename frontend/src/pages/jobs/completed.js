import * as React from 'react';
import QueryString from 'query-string';

import JobsPage from '../../components/JobsPage';

const IndexPage = (props) => {
  let page = parseInt(QueryString.parse(props.location.search).page);
  console.log(page);
  if (page === null) {
    page = 1;
  }
  return (
    <JobsPage t="completed" page={page}>Completed Jobs</JobsPage>
  );
};

export default IndexPage;

export const Head = () => <title>Completed Jobs</title>;

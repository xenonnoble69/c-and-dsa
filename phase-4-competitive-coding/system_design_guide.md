# System Design Interview Guide

## Overview
System design interviews assess your ability to design large-scale distributed systems. This guide covers fundamental concepts, common patterns, and popular system design questions.

## Core Concepts

### 1. Scalability
- **Horizontal Scaling (Scale Out)**: Add more servers
- **Vertical Scaling (Scale Up)**: Add more power to existing server
- **Load Balancing**: Distribute requests across multiple servers
- **Auto-scaling**: Automatically adjust resources based on demand

### 2. Reliability and Availability
- **High Availability**: System remains operational most of the time
- **Fault Tolerance**: System continues operating despite failures
- **Redundancy**: Duplicate components to eliminate single points of failure
- **Disaster Recovery**: Plans for recovering from catastrophic failures

### 3. Data Storage
- **SQL Databases**: ACID properties, complex queries, transactions
- **NoSQL Databases**: Horizontal scaling, eventual consistency
- **Database Sharding**: Partition data across multiple databases
- **Replication**: Master-slave, master-master configurations

### 4. Caching
- **Client-side Caching**: Browser cache, mobile app cache
- **CDN (Content Delivery Network)**: Geographically distributed cache
- **Reverse Proxy Cache**: Nginx, Apache HTTP Server
- **Application-level Cache**: Redis, Memcached
- **Database Cache**: Query result caching

### 5. Communication Protocols
- **HTTP/HTTPS**: Request-response protocol
- **WebSocket**: Real-time bidirectional communication
- **gRPC**: High-performance RPC framework
- **Message Queues**: Asynchronous communication (RabbitMQ, Apache Kafka)

## Design Patterns

### 1. Microservices Architecture
```
Benefits:
- Independent deployment
- Technology diversity
- Fault isolation
- Team autonomy

Challenges:
- Distributed system complexity
- Network latency
- Data consistency
- Service discovery
```

### 2. Event-Driven Architecture
```
Components:
- Event producers
- Event routers
- Event consumers
- Event stores

Use cases:
- Real-time analytics
- Microservices communication
- CQRS (Command Query Responsibility Segregation)
```

### 3. CQRS and Event Sourcing
```
CQRS:
- Separate read and write models
- Optimized for different access patterns

Event Sourcing:
- Store events instead of current state
- Audit trail and replay capability
```

## Common System Design Questions

### 1. Design a URL Shortener (TinyURL)

#### Requirements
- Shorten long URLs to short URLs
- Redirect short URLs to original URLs
- Handle 100M URLs per day
- 100:1 read/write ratio

#### High-Level Design
```
Components:
1. Load Balancer
2. Web Servers
3. Application Servers
4. Database (URL mappings)
5. Cache (Redis)
6. Analytics Service

URL Shortening Algorithm:
- Base62 encoding
- Counter-based approach
- Hash-based approach
```

#### Database Schema
```sql
CREATE TABLE urls (
    id BIGINT PRIMARY KEY,
    short_url VARCHAR(7) UNIQUE,
    long_url TEXT NOT NULL,
    created_at TIMESTAMP,
    expires_at TIMESTAMP,
    user_id BIGINT,
    click_count BIGINT DEFAULT 0
);

CREATE INDEX idx_short_url ON urls(short_url);
CREATE INDEX idx_user_id ON urls(user_id);
```

### 2. Design a Chat System (WhatsApp)

#### Requirements
- One-on-one messaging
- Group chat (up to 100 members)
- Online presence indicator
- Message delivery confirmation
- Push notifications

#### High-Level Design
```
Components:
1. Load Balancer
2. API Gateway
3. Chat Service
4. Presence Service
5. Notification Service
6. Message Database
7. WebSocket Servers
8. Message Queue

Real-time Communication:
- WebSocket connections
- Long polling fallback
- Push notifications for offline users
```

#### Database Design
```sql
-- Users table
CREATE TABLE users (
    user_id BIGINT PRIMARY KEY,
    username VARCHAR(50) UNIQUE,
    email VARCHAR(100),
    last_seen TIMESTAMP
);

-- Conversations table
CREATE TABLE conversations (
    conversation_id BIGINT PRIMARY KEY,
    type ENUM('direct', 'group'),
    created_at TIMESTAMP
);

-- Messages table
CREATE TABLE messages (
    message_id BIGINT PRIMARY KEY,
    conversation_id BIGINT,
    sender_id BIGINT,
    content TEXT,
    message_type ENUM('text', 'image', 'file'),
    created_at TIMESTAMP,
    FOREIGN KEY (conversation_id) REFERENCES conversations(conversation_id),
    FOREIGN KEY (sender_id) REFERENCES users(user_id)
);
```

### 3. Design a Social Media Feed (Facebook/Twitter)

#### Requirements
- Users can post updates
- Users can follow other users
- Generate personalized feed
- Handle millions of users
- Real-time updates

#### High-Level Design
```
Components:
1. User Service
2. Post Service
3. Feed Generation Service
4. Timeline Service
5. Notification Service
6. Media Storage (S3)
7. CDN

Feed Generation Strategies:
- Pull Model (on-demand)
- Push Model (pre-computed)
- Hybrid Model (combination)
```

### 4. Design a Video Streaming Service (YouTube)

#### Requirements
- Upload and store videos
- Stream videos globally
- Support different resolutions
- Video recommendations
- User comments and likes

#### High-Level Design
```
Components:
1. Video Upload Service
2. Video Processing Service
3. Metadata Database
4. CDN for video delivery
5. Recommendation Service
6. User Service
7. Analytics Service

Video Processing:
- Transcoding to multiple formats
- Thumbnail generation
- Quality optimization
```

## Estimation and Capacity Planning

### 1. Back-of-the-envelope Calculations
```
Common Numbers:
- 1 KB = 10³ bytes
- 1 MB = 10⁶ bytes
- 1 GB = 10⁹ bytes
- 1 TB = 10¹² bytes

Request Rates:
- 1M requests/day ≈ 12 requests/second
- 1M requests/second = very high scale

Storage:
- Text: ~1 KB per message
- Image: ~200 KB average
- Video: ~50 MB per minute
```

### 2. QPS (Queries Per Second) Estimation
```
Daily Active Users (DAU): 100M
Average requests per user per day: 10
Total requests per day: 1B
Peak QPS: 1B / (24 * 3600) * 3 ≈ 35K QPS
```

### 3. Storage Estimation
```
New posts per day: 10M
Average post size: 1 KB
Daily storage: 10M * 1 KB = 10 GB
Yearly storage: 10 GB * 365 = 3.65 TB
```

## Technology Stack Choices

### 1. Databases
```
SQL Databases:
- MySQL: General-purpose, ACID compliance
- PostgreSQL: Advanced features, JSON support
- Oracle: Enterprise features

NoSQL Databases:
- MongoDB: Document store, flexible schema
- Cassandra: Wide-column, high availability
- Redis: In-memory, caching and session store
- DynamoDB: Managed NoSQL, serverless
```

### 2. Message Queues
```
Apache Kafka:
- High throughput
- Distributed streaming
- Event sourcing

RabbitMQ:
- Complex routing
- AMQP protocol
- Reliable delivery

Amazon SQS:
- Managed service
- High availability
- Pay-as-you-go
```

### 3. Caching Solutions
```
Redis:
- In-memory data structure store
- Persistence options
- Pub/Sub messaging

Memcached:
- Simple key-value cache
- High performance
- Distributed caching

Elasticsearch:
- Search and analytics
- Full-text search
- Real-time indexing
```

## Monitoring and Observability

### 1. Metrics to Monitor
```
Application Metrics:
- Request rate (QPS)
- Error rate
- Response time (latency)
- Throughput

Infrastructure Metrics:
- CPU utilization
- Memory usage
- Disk I/O
- Network bandwidth

Business Metrics:
- Daily active users
- Conversion rates
- Revenue per user
```

### 2. Logging and Tracing
```
Centralized Logging:
- ELK Stack (Elasticsearch, Logstash, Kibana)
- Fluentd for log collection
- Structured logging (JSON format)

Distributed Tracing:
- Jaeger or Zipkin
- OpenTelemetry
- Request correlation IDs
```

## Security Considerations

### 1. Authentication and Authorization
```
Authentication:
- JWT tokens
- OAuth 2.0
- Multi-factor authentication

Authorization:
- Role-based access control (RBAC)
- Attribute-based access control (ABAC)
- API rate limiting
```

### 2. Data Security
```
Encryption:
- HTTPS/TLS for data in transit
- AES encryption for data at rest
- Database encryption

Input Validation:
- SQL injection prevention
- XSS protection
- Input sanitization
```

## Interview Process and Tips

### 1. Typical Flow
```
1. Requirements Clarification (5-10 min)
   - Functional requirements
   - Non-functional requirements
   - Scale and constraints

2. High-Level Design (10-15 min)
   - Core components
   - Data flow
   - API design

3. Detailed Design (15-20 min)
   - Database schema
   - Detailed algorithms
   - Specific technologies

4. Scale and Optimize (5-10 min)
   - Bottlenecks identification
   - Scaling strategies
   - Trade-offs discussion
```

### 2. Do's and Don'ts
```
Do's:
- Ask clarifying questions
- Start with simple design
- Think out loud
- Consider trade-offs
- Discuss alternatives

Don'ts:
- Jump into details too quickly
- Over-engineer the solution
- Ignore scalability
- Forget about edge cases
- Be dogmatic about technologies
```

### 3. Common Mistakes
```
- Not asking enough questions
- Designing for current scale only
- Ignoring data consistency
- Not considering failure scenarios
- Poor time management
- Getting stuck on minor details
```

## Practice Resources

### Books
- "Designing Data-Intensive Applications" by Martin Kleppmann
- "System Design Interview" by Alex Xu
- "Building Microservices" by Sam Newman

### Online Resources
- High Scalability blog
- AWS Architecture Center
- Google Cloud Architecture Framework
- System Design Primer (GitHub)

### Practice Platforms
- Pramp (mock interviews)
- InterviewBit System Design
- Grokking the System Design Interview
- LeetCode System Design section

Remember: System design is about trade-offs. There's no single "correct" answer, but rather multiple valid approaches with different pros and cons. Focus on understanding the requirements, making reasonable assumptions, and justifying your design decisions.
